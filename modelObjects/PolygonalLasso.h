#pragma once

#include "infrastructure/ModelObject.h"
#include <QPoint>
#include <QPolygon>

class PolygonalLasso : public ModelObject
{
    Q_OBJECT

    Q_PROPERTY(QPolygon LassoPoints READ getPoints)

public:
    PolygonalLasso();
    virtual ~PolygonalLasso();

    void insertPoint(const QPoint& fPoint);

    QPolygon getPoints() const;

private:
    QPolygon mLassoPoints;
};
