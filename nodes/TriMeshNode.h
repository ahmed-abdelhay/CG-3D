#pragma once

#include <osg/Geode>
#include "core/TriMesh.h"
#include "infrastructure/Type.h"

class TriMeshNode : public osg::Geode , public Type
{
public:
    META_Node(osg, TriMeshNode)

    TriMeshNode();
    TriMeshNode(const TriMesh& fMesh);
    TriMeshNode(const TriMeshNode& fCopy, const osg::CopyOp& fCopyOp=osg::CopyOp::SHALLOW_COPY);

    void setColor(const osg::Vec4f& fColor);
    osg::Vec4f getColor();

    void setMesh(const TriMesh& fMesh);
    TriMesh getMesh();

    void update();

private:
    TriMesh mMesh;
    osg::Vec4f mColor;
};
