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

    void setContext(ApplicationContext *_context) override;

private:
    void notify(const std::shared_ptr<Event> & _event) override;

    void handleRead3DObjectEvent(const std::shared_ptr<Read3DObjectEvent>& _event);
    void handleWrite3DObjectEvent(const std::shared_ptr<Write3DObjectEvent> &_event);

    std::string getMeshNameFromFileName(const std::string& _fileName) const;
};
