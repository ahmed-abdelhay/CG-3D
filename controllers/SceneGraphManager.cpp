#include "SceneGraphManager.h"
#include "infrastructure/ApplicationContext.h"
#include "modelObjects/ThreeDObject.h"

#include "nodes/CordinateSystemNode.h"
#include "nodes/TriMeshNode.h"

#include <osg/Light>
#include <osg/LightSource>
#include <osg/Group>
#include <osg/Material>

SceneGraphManager::SceneGraphManager()
{}

SceneGraphManager::~SceneGraphManager()
{
    if (context())
    {
        unsubscribeToContainerChanged(context());
        unsubscribeToEvents(context());
    }
}

void SceneGraphManager::buildScene()
{
    mRootNode = new osg::Group;
    mRootNode->setName("root");

    // Set material for basic lighting and enable depth tests. Else, the sphere
    // will suffer from rendering errors.

    auto stateSet = mRootNode->getOrCreateStateSet();
    auto material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

    auto cordinateSystemNode = new CoordinateSystemNode;
    cordinateSystemNode->setName("coordinate-system");
    //mRootNode->addChild(cordinateSystemNode);

    // set the lights
    osg::ref_ptr<osg::Light> light = new osg::Light(0);
    light->setPosition(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
    light->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    light->setSpecular(osg::Vec4(0.5f, 0.5f, 0.5f, 1.0f));
    light->setAmbient( osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
    light->setName("light");

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();
    lightSource->setLight(light);
    lightSource->setName("light-source");

    mRootNode->addChild(lightSource);

    m3DSurfacesGroup = new osg::Group;
    m3DSurfacesGroup->setName("surface-group");
    mRootNode->addChild(m3DSurfacesGroup);
}

osg::Node *SceneGraphManager::getRootNode()
{
    return mRootNode.get();
}

void SceneGraphManager::setContext(ApplicationContext *fContext)
{
    mContext = fContext;
    if (context())
    {
        subscribeToContainerChanged(fContext);
        subscribeToEvents(fContext);
    }
}

void SceneGraphManager::notifyContainerChanged(const std::shared_ptr<Type> &fObject, ContainerChangeType fChangeType)
{
    if(fObject->metaObject()->className() == ThreeDObjectType)
    {
        switch (fChangeType)
        {
        case ContainerChangeType::OBJECT_ADDED:
            if (auto threeDObject = dynamic_cast<ThreeDObject*>(fObject.get()))
            {
                auto threeDObjectNode = new TriMeshNode(threeDObject->getID(), threeDObject->getMesh(), threeDObject->getColor());
                threeDObjectNode->setContext(context());
                m3DSurfacesGroup->addChild(threeDObjectNode);
                threeDObjectNode->update();
            }
            break;
        case ContainerChangeType::OBJECT_REMOVED:
            if (auto threeDObject = dynamic_cast<ThreeDObject*>(fObject.get()))
            {
                auto objectID = threeDObject->getID();
                auto surfaceNodesCount = m3DSurfacesGroup->getNumChildren();
                for (unsigned int i = 0; i < surfaceNodesCount; ++i)
                {
                    if (auto node = dynamic_cast<TriMeshNode*>(m3DSurfacesGroup->getChild(i)))
                    {
                        if (node->get3DobjectID() == objectID)
                        {
                            m3DSurfacesGroup->removeChild(i);
                            return;
                        }
                    }
                }
            }
            break;
        }
    }
}

void SceneGraphManager::notify(const std::shared_ptr<Event> &fEvent)
{

}
