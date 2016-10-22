#include "PolygonalLasso.h"
#include "infrastructure/Common.h"

PolygonalLasso::PolygonalLasso()
{}

PolygonalLasso::~PolygonalLasso()
{}

void PolygonalLasso::insertPoint(const QPoint &_point)
{
    mLassoPoints.push_back(_point);
    emit propertyChanged(this, LassoPointsType);
}

QPolygon PolygonalLasso::getPoints() const
{
    return mLassoPoints;
}
