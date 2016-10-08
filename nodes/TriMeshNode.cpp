#include "TriMeshNode.h"

#include <osg/Geometry>

TriMeshNode::TriMeshNode()
    : osg::Geode(),
      mColor(1.0f, 0.0f, 0.0f, 1.0f)
{}

TriMeshNode::TriMeshNode(const TriMesh &fMesh)
    : osg::Geode(),
      mMesh(fMesh),
      mColor(1.0f, 0.0f, 0.0f, 1.0f)
{}

TriMeshNode::TriMeshNode(const TriMeshNode& fCopy, const osg::CopyOp &fCopyOp)
    :osg::Geode(fCopy, fCopyOp),
      mMesh(fCopy.mMesh),
      mColor(fCopy.mColor)
{}

void TriMeshNode::setColor(const osg::Vec4f &fColor)
{
    mColor = fColor;
}

osg::Vec4f TriMeshNode::getColor()
{
    return mColor;
}

void TriMeshNode::setMesh(const TriMesh &fMesh)
{
    mMesh = fMesh;
}

TriMesh TriMeshNode::getMesh()
{
    return mMesh;
}

void TriMeshNode::update()
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(mMesh.n_vertices());

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(mMesh.n_vertices());

    mMesh.request_face_normals();
    mMesh.request_vertex_normals();

    mMesh.update_face_normals();
    mMesh.update_vertex_normals();

    int counter = 0;

    for (const auto& vh : mMesh.vertices())
    {
        auto& point = mMesh.point(vh);
        auto& normal = mMesh.normal(vh);
        (*vertices)[counter].set(point[0], point[1], point[2]);
        (*normals)[counter++].set(normal[2], normal[1], normal[0]);
    }

    mMesh.release_face_normals();
    mMesh.release_vertex_normals();

    osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(GL_TRIANGLES, 3 * mMesh.n_faces());
    counter = 0;

    for (const auto& fh : mMesh.faces())
    {
        for (const auto& vh : mMesh.fv_range(fh))
            (*indices)[counter++] = vh.idx();
    }

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(1);
    (*colors)[0].set(mColor[0], mColor[1], mColor[2], mColor[3]);

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
    geometry->setVertexArray(vertices.get());
    geometry->setNormalArray(normals.get());
    geometry->addPrimitiveSet(indices.get());
    geometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
    geometry->setColorArray(colors);
    geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

    if (getNumDrawables() == 0)
        addDrawable(geometry);
    else
        replaceDrawable(getDrawable(0), geometry);
}
