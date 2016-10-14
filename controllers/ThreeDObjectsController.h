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

    void notify(const std::shared_ptr<Event> &fEvent) override;
    void setContext(ApplicationContext *fContext) override;

private:
    void handleDeleteSelected3DObjectEvent(const std::shared_ptr<DeleteSelected3DObjectEvent> &fEvent);
    void handleChange3DObjectColorEvent(const std::shared_ptr<Change3DObjectColorEvent> &fEvent);
};
