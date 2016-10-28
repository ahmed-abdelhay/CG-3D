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

#include <QDebug>
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
    auto isPointInsidePolygon = [](const std::vector<OpenMesh::Vec3f>& _polygon, const OpenMesh::Vec3f& _point) -> bool
    {
        int i, j;
        bool result = false;
        auto polygonLassoPointsCount = _polygon.size();

        for (i = 0, j = polygonLassoPointsCount - 1; i < polygonLassoPointsCount; j = i++)
        {
            if ( ((_polygon[i][1] > _point[1]) != (_polygon[j][1] > _point[1])) &&
                 (_point[0] < (_polygon[j][0] - _polygon[i][0]) * (_point[1] - _polygon[i][1]) / (_polygon[j][1] - _polygon[i][1]) + _polygon[i][0]) )
                result = !result;
        }
        return result;
    };

    if (auto selected3DSurface = mContext->selectionManager()->getSelectedObject<ThreeDObject>(ThreeDObjectType))
    {
        auto viewProjectionMatrix = _event->viewMatrix * _event->projectionMatrix;
        auto lasso = std::dynamic_pointer_cast<PolygonalLasso>(mContext->dataStore()->getAllObjectOfType(PolygonalLassoType)[0]);
        auto lassoPoints = lasso->getPoints();

        auto mesh = selected3DSurface->getMesh();
        mesh->clearFaceSelection();


        for (auto& point : lassoPoints)
        {
            point = 2 * point - OpenMesh::Vec3f(1,1,0);
        }

        mesh->request_face_status();
        mesh->request_vertex_status();
        mesh->request_edge_status();

        for (const auto& fh : mesh->faces())
        {
            for (const auto& vh : mesh->fv_range(fh))
            {
                auto point = mesh->point(vh);
                auto projectedPoint = osg::Vec4d(point[0], point[1], point[2], 1.0f) * viewProjectionMatrix;
                projectedPoint /= projectedPoint[3];
                if (isPointInsidePolygon(lassoPoints, OpenMesh::Vec3f(projectedPoint[0], projectedPoint[1], 0.0f)))
                {
                    mesh->delete_face(fh, false);
                    break;
                }
            }
        }

        mesh->garbage_collection();

        mesh->release_face_status();
        mesh->release_vertex_status();
        mesh->release_edge_status();

        selected3DSurface->setMesh(mesh);
    }
}
