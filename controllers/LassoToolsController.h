#pragma once

#include <memory>

#include "infrastructure/Type.h"
#include "infrastructure/ApplicationContextProvider.h"
#include "infrastructure/EventHandler.h"

class LassoToolChangeEvent;
class AddLassoPointEvent;
class ApplyLassoEvent;

class LassoToolsController : public Type, public ApplicationContextProvider, public EventHandler
{
public:
    LassoToolsController();
    virtual ~LassoToolsController();

    void setContext(ApplicationContext *_context) override;

private:
    void notify(const std::shared_ptr<Event> &_event) override;

    void handleLassoToolStateChangeEvent(const std::shared_ptr<LassoToolChangeEvent>& _event);
    void handleAddLassoPointEvent(const std::shared_ptr<AddLassoPointEvent>& _event);
    void handleApplyLassoEvent(const std::shared_ptr<ApplyLassoEvent>& _event);
};
