#include "PolygonalLasso.h"
#include "infrastructure/Common.h"

PolygonalLasso::PolygonalLasso()
{}

PolygonalLasso::~PolygonalLasso()
{}

void PolygonalLasso::insertPoint(const OpenMesh::Vec3f &_point)
{
    mLassoPoints.push_back(_point);
    emit propertyChanged(this, LassoPointsType);
}

void PolygonalLasso::clearPoints()
{
    mLassoPoints.clear();
    emit propertyChanged(this, LassoPointsType);
}

std::vector<OpenMesh::Vec3f> PolygonalLasso::getPoints() const
{
    return mLassoPoints;
}
