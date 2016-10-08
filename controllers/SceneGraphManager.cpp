#include "SceneGraphManager.h"
#include "ApplicationContext.h"

#include <osg/Light>
#include <osg/LightSource>
#include <osg/Group>
#include <osg/Material>

#include "CordinateSystemNode.h"

//#include <OpenMesh/Core/IO/MeshIO.hh>
//#include "TriMesh.h"
//#include "TriMeshNode.h"

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

osg::Node *SceneGraphManager::buildScene()
{

    osg::ref_ptr<osg::Group> rootGroup = new osg::Group;
    rootGroup->setName("root");

    auto cordinateSystemNode = new CoordinateSystemNode;
    cordinateSystemNode->setName("coordinate-system");
    rootGroup->addChild(cordinateSystemNode);

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

    rootGroup->addChild(lightSource);

    osg::ref_ptr<osg::Group> surfaceGroup = new osg::Group;
    surfaceGroup->setName("surface-group");


    //    std::string meshFileName = "/home/ahmed/Desktop/bunny.ply";
    //    TriMesh mesh;
    //    auto f =  OpenMesh::IO::read_mesh(mesh, meshFileName);
    //    auto meshNode = new TriMeshNode(mesh);
    //    meshNode->setColor(osg::Vec4(1,0,0,1));
    //    meshNode->update();

    //    for (auto vh: mesh.vertices())
    //        mesh.set_point(vh, mesh.point(vh) + 0.5*OpenMesh::Vec3f(1,1,1));

    //    auto meshNode1 = new TriMeshNode(mesh);
    //    meshNode1->setColor(osg::Vec4(1,1,0,1));
    //    meshNode1->update();

    //    surfaceGroup->addChild(meshNode);
    //    surfaceGroup->addChild(meshNode1);

    rootGroup->addChild(surfaceGroup);

    // Set material for basic lighting and enable depth tests. Else, the sphere
    // will suffer from rendering errors.

    auto stateSet = rootGroup->getOrCreateStateSet();
    auto material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

    return rootGroup.release();
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

}

void SceneGraphManager::notify(const std::shared_ptr<Event> &fEvent)
{

}
