#pragma once

#include <osg/ref_ptr>

#include "infrastructure/ApplicationContextProvider.h"
#include "infrastructure/ContainerChangedHandler.h"
#include "infrastructure/EventHandler.h"

namespace osg {class Group;}
namespace osg {class Node;}

class SceneGraphManager : public EventHandler, public ContainerChangedHandler,
        public ApplicationContextProvider
{
public:
    SceneGraphManager();
    virtual ~SceneGraphManager();

    void buildScene();

    osg::Node *getRootNode();

    void setContext(ApplicationContext* fContext) override;
    void notifyContainerChanged(const std::shared_ptr<Type> &fObject, ContainerChangeType fChangeType) override;
    void notify(const std::shared_ptr<Event> &fEvent) override;

private:
    osg::ref_ptr<osg::Group> mRootNode;
    osg::ref_ptr<osg::Group> m3DSurfacesGroup;
};
