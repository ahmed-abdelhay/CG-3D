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

void ThreeDObject::setColor(QColor fColor)
{
    mColor = fColor;
    emit propertyChanged(this, ColorType);
}

void ThreeDObject::setName(std::string fName)
{
    mName = fName;
    emit propertyChanged(this, NameType);
}

void ThreeDObject::setMesh(const std::shared_ptr<TriMesh>& fMesh)
{
    mMesh = fMesh;
    emit propertyChanged(this, MeshType);
}
