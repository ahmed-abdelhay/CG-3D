#pragma once

#include "infrastructure/ApplicationContextProvider.h"
#include "infrastructure/ContainerChangedHandler.h"
#include "infrastructure/EventHandler.h"

namespace osg {class Node;}

class SceneGraphManager : public EventHandler, public ContainerChangedHandler,
        public ApplicationContextProvider
{
public:
    SceneGraphManager();
    virtual ~SceneGraphManager();

    osg::Node* buildScene();

    void setContext(ApplicationContext* fContext) override;

    // ContainerChangedHandler interface
    void notifyContainerChanged(const std::shared_ptr<Type> &fObject, ContainerChangeType fChangeType) override;

    // EventHandler interface
    void notify(const std::shared_ptr<Event> &fEvent) override;

private:

};
