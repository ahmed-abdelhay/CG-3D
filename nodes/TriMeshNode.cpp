#include "TriMeshNode.h"

#include <osg/Geometry>

#include "infrastructure/Common.h"
#include "infrastructure/ApplicationContext.h"
#include "modelObjects/ThreeDObject.h"
#include "core/TriMesh.h"

TriMeshNode::TriMeshNode()
    : osg::Geode(),
      m3DObjectID(-1),
      mMesh(nullptr),
      mColor(1.0f, 0.0f, 0.0f, 1.0f)
{}

TriMeshNode::TriMeshNode(const size_t &_3DObjectID, const std::shared_ptr<TriMesh> &_mesh, const QColor &_color)
    : osg::Geode(),
      m3DObjectID(_3DObjectID),
      mMesh(_mesh),
      mColor(_color.redF(), _color.greenF(), _color.blueF(), _color.alphaF())
{}

TriMeshNode::TriMeshNode(const TriMeshNode& _copy, const osg::CopyOp &_copyOp)
    :osg::Geode(_copy, _copyOp),
      m3DObjectID(_copy.m3DObjectID),
      mMesh(_copy.mMesh),
      mColor(_copy.mColor)
{}

TriMeshNode::~TriMeshNode()
{
    if (context())
    {
        unsubscribePropertyChangedOnType(ThreeDObjectType, context());
    }
}

void TriMeshNode::setColor(const QColor &_color)
{
    mColor[0] = _color.redF();
    mColor[1] = _color.greenF();
    mColor[2] = _color.blueF();
    mColor[3] = _color.alphaF();
}

QColor TriMeshNode::getColor() const
{
    return QColor(mColor[0] * 255, mColor[1] * 255, mColor[2] * 255, mColor[3] * 255);
}

void TriMeshNode::setMesh(const std::shared_ptr<TriMesh> &_mesh)
{
    mMesh = _mesh;
}

std::shared_ptr<TriMesh> TriMeshNode::getMesh() const
{
    return mMesh;
}

size_t TriMeshNode::get3DobjectID() const
{
    return m3DObjectID;
}

void TriMeshNode::update()
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(mMesh->n_vertices());

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(mMesh->n_vertices());

    mMesh->request_face_normals();
    mMesh->request_vertex_normals();

    mMesh->update_face_normals();
    mMesh->update_vertex_normals();

    int counter = 0;

    for (const auto& vh : mMesh->vertices())
    {
        auto& point = mMesh->point(vh);
        auto& normal = mMesh->normal(vh);
        (*vertices)[counter].set(point[0], point[1], point[2]);
        (*normals)[counter++].set(normal[2], normal[1], normal[0]);
    }

    mMesh->release_face_normals();
    mMesh->release_vertex_normals();

    osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(GL_TRIANGLES, 3 * mMesh->n_faces());
    counter = 0;

    for (const auto& fh : mMesh->faces())
    {
        for (const auto& vh : mMesh->fv_range(fh))
            (*indices)[counter++] = vh.idx();
    }

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(mMesh->n_faces());

    auto selectedFaces = mMesh->getSelectedFaces();

    for (int i = 0; i < mMesh->n_faces(); ++i)
        (*colors)[i].set(mColor[0], mColor[1], mColor[2], mColor[3]);

    for (const auto& fh : selectedFaces)
        (*colors)[fh.idx()].set(1.0f, 0.0f, 0.0f, 1.0f);

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
    geometry->setVertexArray(vertices.get());
    geometry->setNormalArray(normals.get());
    geometry->addPrimitiveSet(indices.get());
    geometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
    geometry->setColorArray(colors);
    geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);

    if (getNumDrawables() == 0)
        addDrawable(geometry);
    else
        replaceDrawable(getDrawable(0), geometry);
}

void TriMeshNode::propertyChanged(Type *_source, const std::string &_propertyName)
{
    if (_source->getID() == m3DObjectID)
    {
        if (auto object = dynamic_cast<ThreeDObject*>(_source))
        {
            if (_propertyName == ColorType)
            {
                mColor[0] = object->getColor().redF();
                mColor[1] = object->getColor().greenF();
                mColor[2] = object->getColor().blueF();
                mColor[3] = object->getColor().alphaF();
            }
            else if (_propertyName == MeshType)
            {
                mMesh = object->getMesh();
            }

            update();
        }
    }
}

void TriMeshNode::setContext(ApplicationContext *_context)
{
    mContext = _context;
    subscribePropertyChangedOnType(ThreeDObjectType, _context);
}
