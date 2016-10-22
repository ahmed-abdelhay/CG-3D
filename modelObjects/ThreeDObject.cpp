#include "ThreeDObject.h"
#include "infrastructure/Common.h"

ThreeDObject::ThreeDObject()
{}

ThreeDObject::~ThreeDObject()
{}

QColor ThreeDObject::getColor() const
{
    return mColor;
}

std::string ThreeDObject::getName() const
{
    return mName;
}

std::shared_ptr<TriMesh> ThreeDObject::getMesh() const
{
    return mMesh;
}

void ThreeDObject::setColor(QColor _color)
{
    mColor = _color;
    emit propertyChanged(this, ColorType);
}

void ThreeDObject::setName(std::string _name)
{
    mName = _name;
    emit propertyChanged(this, NameType);
}

void ThreeDObject::setMesh(const std::shared_ptr<TriMesh>& _mesh)
{
    mMesh = _mesh;
    emit propertyChanged(this, MeshType);
}
