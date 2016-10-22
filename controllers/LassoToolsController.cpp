#include "LassoToolsController.h"
#include "events/LassoToolChangeEvent.h"
#include "events/AddLassoPointEvent.h"
#include "modelObjects/PolygonalLasso.h"
#include "infrastructure/ApplicationContext.h"
#include "infrastructure/ApplicationDatastore.h"
#include "infrastructure/Common.h"


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
