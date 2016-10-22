#pragma once

#include <osg/ref_ptr>

#include "infrastructure/Type.h"
#include "infrastructure/ApplicationContextProvider.h"
#include "infrastructure/ContainerChangedHandler.h"
#include "infrastructure/EventHandler.h"

namespace osg {class Group;}
namespace osg {class Node;}

class SceneGraphManager : public Type, public EventHandler, public ContainerChangedHandler,
        public ApplicationContextProvider
{
public:
    SceneGraphManager();
    virtual ~SceneGraphManager();

    void buildScene();

    osg::Node *getRootNode();

    void setContext(ApplicationContext* _context) override;

private:
    void notifyContainerChanged(const std::shared_ptr<Type> &_object, ContainerChangeType _changeType) override;
    void notify(const std::shared_ptr<Event> &_event) override;

    osg::ref_ptr<osg::Group> mRootNode;
    osg::ref_ptr<osg::Group> m3DSurfacesGroup;
};
