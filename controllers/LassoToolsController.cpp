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

void LassoToolsController::setContext(ApplicationContext *fContext)
{
    mContext = fContext;
    subscribeToEvents(context());
}

void LassoToolsController::notify(const std::shared_ptr<Event> &fEvent)
{
    if (auto event = std::dynamic_pointer_cast<LassoToolChangeEvent>(fEvent))
        handleLassoToolStateChangeEvent(event);
    else if (auto event = std::dynamic_pointer_cast<AddLassoPointEvent>(fEvent))
        handleAddLassoPointEvent(event);
}

void LassoToolsController::handleLassoToolStateChangeEvent(const std::shared_ptr<LassoToolChangeEvent> &fEvent)
{
    switch (fEvent->lassoToolType)
    {
    case LassoToolChangeEvent::LassoToolType::POLYGONAL_LASSO_TOOL:
        if (fEvent->toolState)
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

void LassoToolsController::handleAddLassoPointEvent(const std::shared_ptr<AddLassoPointEvent> &fEvent)
{
    auto lassos = mContext->dataStore()->getAllObjectOfType(PolygonalLassoType);
    for (const auto& lasso : lassos)
    {
        std::dynamic_pointer_cast<PolygonalLasso>(lasso)->insertPoint(fEvent->lassoPoint);
    }
}
