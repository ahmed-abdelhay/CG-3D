#include "PolygonalLasso.h"
#include "infrastructure/Common.h"

PolygonalLasso::PolygonalLasso()
{}

PolygonalLasso::~PolygonalLasso()
{}

void PolygonalLasso::insertPoint(const QPoint &fPoint)
{
    mLassoPoints.push_back(fPoint);
    emit propertyChanged(this, LassoPointsType);
}

QPolygon PolygonalLasso::getPoints() const
{
    return mLassoPoints;
}
