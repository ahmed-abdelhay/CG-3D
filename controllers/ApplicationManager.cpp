#include "ApplicationManager.h"
#include "infrastructure/ApplicationContext.h"
#include "SceneGraphManager.h"
#include "MeshIOController.h"

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
    auto meshIOController = std::make_shared<MeshIOController>();
    meshIOController->setContext(mContext.get());
    mContext->dataStore()->insertObject(meshIOController);
}

void ApplicationManager::initializeSceneGraph()
{
    std::shared_ptr<SceneGraphManager> sceneGraphManager(new SceneGraphManager());
    sceneGraphManager->setContext(mContext.get());
    mContext->dataStore()->insertObject(sceneGraphManager);
    sceneGraphManager->buildScene();
    mSceneGraphRootNode = osg::ref_ptr<osg::Node>(sceneGraphManager->getRootNode());
}

osg::ref_ptr<osg::Node> ApplicationManager::getSceneGraphRootNode()
{
    return mSceneGraphRootNode;
}

ApplicationContext *ApplicationManager::context()
{
    return mContext.get();
}
