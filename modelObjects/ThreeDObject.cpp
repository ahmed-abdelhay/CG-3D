#include "ThreeDObject.h"

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
    fColor = fColor;
}

void ThreeDObject::setName(std::string fName)
{
    fName = fName;
}

void ThreeDObject::setMesh(const std::shared_ptr<TriMesh>& fMesh)
{
    mMesh = fMesh;
}
