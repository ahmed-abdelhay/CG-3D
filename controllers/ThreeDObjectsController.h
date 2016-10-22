#pragma once

#include <memory>
#include <string>

#include "infrastructure/Type.h"
#include "infrastructure/ApplicationContextProvider.h"
#include "infrastructure/EventHandler.h"

class Change3DObjectColorEvent;
class DeleteSelected3DObjectEvent;

// handle all the 3D objects I/O operations
class ThreeDObjectsController : public Type, public ApplicationContextProvider, public EventHandler
{
public:
    ThreeDObjectsController();
    virtual ~ThreeDObjectsController();

    void setContext(ApplicationContext *_context) override;

private:
    void notify(const std::shared_ptr<Event> &_event) override;

    void handleDeleteSelected3DObjectEvent(const std::shared_ptr<DeleteSelected3DObjectEvent> &_event);
    void handleChange3DObjectColorEvent(const std::shared_ptr<Change3DObjectColorEvent> &_event);
};
