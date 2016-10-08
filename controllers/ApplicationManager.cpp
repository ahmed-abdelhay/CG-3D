#include "ApplicationManager.h"
#include "infrastructure/ApplicationContext.h"
#include "SceneGraphManager.h"

#include <osg/Node>

ApplicationManager::ApplicationManager()
    : mContext(new ApplicationContext())
{
    initializeControllers();
    initializeSceneGraph();
}

ApplicationManager::~ApplicationManager()
{}

void ApplicationManager::initializeControllers()
{

}

void ApplicationManager::initializeSceneGraph()
{
    std::shared_ptr<SceneGraphManager> sceneGraphManager(new SceneGraphManager());
    sceneGraphManager->setContext(mContext.get());
    mContext->dataStore()->insertObject(sceneGraphManager);
    mSceneGraphRootNode = osg::ref_ptr<osg::Node>(sceneGraphManager->buildScene());
}

osg::ref_ptr<osg::Node> ApplicationManager::getSceneGraphRootNode()
{
    return mSceneGraphRootNode;
}

ApplicationContext *ApplicationManager::context()
{
    return mContext.get();
}
