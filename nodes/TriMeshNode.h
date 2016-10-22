#pragma once

#include <osg/Geode>
#include <memory>
#include <QColor>

#include "infrastructure/ApplicationContextProvider.h"
#include "infrastructure/PropertyChangedHandler.h"

class TriMesh;

// this node is to render the 3D meshes
class TriMeshNode : public osg::Geode , public ApplicationContextProvider, public PropertyChangedHandler
{
public:
    META_Node(osg, TriMeshNode)

    TriMeshNode();
    TriMeshNode(const size_t& _3DObjectID, const std::shared_ptr<TriMesh>& _mesh, const QColor& _color);
    TriMeshNode(const TriMeshNode& _copy, const osg::CopyOp& _copyOp=osg::CopyOp::SHALLOW_COPY);

    virtual ~TriMeshNode();

    void setColor(const QColor &_color);
    QColor getColor() const;

    void setMesh(const std::shared_ptr<TriMesh> &_mesh);
    std::shared_ptr<TriMesh> getMesh() const;

    size_t get3DobjectID() const;

    // update the node
    void update();

    void propertyChanged(Type *_source, const std::string &_propertyName);
    void setContext(ApplicationContext *_context);

private:
    size_t m3DObjectID; // the unique id of the object that the node represnt
    std::shared_ptr<TriMesh> mMesh;
    osg::Vec4f mColor;
};
