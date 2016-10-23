#include "LassoToolsController.h"
#include "events/LassoToolChangeEvent.h"
#include "events/AddLassoPointEvent.h"
#include "events/ApplyLassoEvent.h"
#include "modelObjects/PolygonalLasso.h"
#include "modelObjects/ThreeDObject.h"
#include "infrastructure/ApplicationContext.h"
#include "infrastructure/SelectionManager.h"
#include "infrastructure/ApplicationDatastore.h"
#include "infrastructure/Common.h"

#include <osg/Matrixd>
#include <osg/Vec3d>

#include <fstream>

LassoToolsController::LassoToolsController()
{}

LassoToolsController::~LassoToolsController()
{
    if (context())
        unsubscribeToEvents(context());
}

void LassoToolsController::setContext(ApplicationContext *_context)
{
    mContext = _context;
    subscribeToEvents(context());
}

void LassoToolsController::notify(const std::shared_ptr<Event> &_event)
{
    if (auto event = std::dynamic_pointer_cast<LassoToolChangeEvent>(_event))
        handleLassoToolStateChangeEvent(event);
    else if (auto event = std::dynamic_pointer_cast<AddLassoPointEvent>(_event))
        handleAddLassoPointEvent(event);
    else if (auto event = std::dynamic_pointer_cast<ApplyLassoEvent>(_event))
        handleApplyLassoEvent(event);
}

void LassoToolsController::handleLassoToolStateChangeEvent(const std::shared_ptr<LassoToolChangeEvent> &_event)
{
    switch (_event->lassoToolType)
    {
    case LassoToolChangeEvent::LassoToolType::POLYGONAL_LASSO_TOOL:
        if (_event->toolState)
        {
            auto polygonalLasso = std::make_shared<PolygonalLasso>();
            context()->dataStore()->insertObject(polygonalLasso);
        }
        else
        {
            auto lassoObjects = context()->dataStore()->getAllObjectOfType(PolygonalLassoType);
            for (const auto& lassoObject : lassoObjects)
                context()->dataStore()->removeObject(lassoObject);
        }
        break;
    }
}

void LassoToolsController::handleAddLassoPointEvent(const std::shared_ptr<AddLassoPointEvent> &_event)
{
    auto lassos = mContext->dataStore()->getAllObjectOfType(PolygonalLassoType);
    for (const auto& lasso : lassos)
    {
        std::dynamic_pointer_cast<PolygonalLasso>(lasso)->insertPoint(_event->lassoPoint);
    }
}

void LassoToolsController::handleApplyLassoEvent(const std::shared_ptr<ApplyLassoEvent> &_event)
{
    if (auto selected3DSurface = mContext->selectionManager()->getSelectedObject<ThreeDObject>(ThreeDObjectType))
    {
        auto viewProjectionMatrixInverse = osg::Matrixd::inverse(_event->projectionMatrix * _event->viewMatrix);
        auto lasso = std::dynamic_pointer_cast<PolygonalLasso>(mContext->dataStore()->getAllObjectOfType(PolygonalLassoType)[0]);
        std::vector<osg::Vec3d> topPoints, basePoints;
        std::ofstream fout("/home/ahmed/test.xyz");

        for (const auto& point : lasso->getPoints())
        {
            auto topPoint = viewProjectionMatrixInverse * osg::Vec3d(point.x(), point.y(), -1);
            auto basePoint = viewProjectionMatrixInverse * osg::Vec3d(point.x(), point.y(), 1);
            topPoints.emplace_back(topPoint);
            basePoints.emplace_back(basePoint);
            fout << topPoint[0] << " " << topPoint[1] << " " << topPoint[2] <<std::endl;
            fout << basePoint[0] << " " << basePoint[1] << " " << basePoint[2] <<std::endl;
        }
    }
}
