#pragma once

#include <memory>
#include <string>

#include "infrastructure/Type.h"
#include "infrastructure/ApplicationContextProvider.h"
#include "infrastructure/EventHandler.h"

class Read3DObjectEvent;
class Write3DObjectEvent;

// handle all the 3D objects I/O operations
class MeshIOController : public Type, public ApplicationContextProvider, public EventHandler
{
public:
    MeshIOController();
    virtual ~MeshIOController();

    void notify(const std::shared_ptr<Event> &fEvent) override;
    void setContext(ApplicationContext *fContext) override;

private:
    void handleRead3DObjectEvent(const std::shared_ptr<Read3DObjectEvent>& fEvent);
    void handleWrite3DObjectEvent(const std::shared_ptr<Write3DObjectEvent> &fEvent);

    std::string getMeshNameFromFileName(const std::string& fFileName) const;
};
