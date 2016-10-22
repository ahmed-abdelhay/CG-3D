#pragma once

#include <memory>

#include "infrastructure/Type.h"
#include "infrastructure/ApplicationContextProvider.h"
#include "infrastructure/EventHandler.h"

class LassoToolChangeEvent;
class AddLassoPointEvent;

class LassoToolsController : public Type, public ApplicationContextProvider, public EventHandler
{
public:
    LassoToolsController();
    virtual ~LassoToolsController();

    void setContext(ApplicationContext *fContext) override;

private:
    void notify(const std::shared_ptr<Event> &fEvent) override;

    void handleLassoToolStateChangeEvent(const std::shared_ptr<LassoToolChangeEvent>& fEvent);
    void handleAddLassoPointEvent(const std::shared_ptr<AddLassoPointEvent>& fEvent);
};
