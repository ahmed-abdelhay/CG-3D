#pragma once

#include <memory>
#include <osg/ref_ptr>

class ApplicationContext;
namespace osg { class Node;}

// the application manager is responsible for initializing the application
// and the scene graph
class ApplicationManager
{
public:
    ApplicationManager();
    virtual ~ApplicationManager();

    void initializeControllers();
    void initializeSceneGraph();

    osg::ref_ptr<osg::Node> getSceneGraphRootNode();
    ApplicationContext* context();

private:
    std::shared_ptr<ApplicationContext> mContext;
    osg::ref_ptr<osg::Node> mSceneGraphRootNode;
};
