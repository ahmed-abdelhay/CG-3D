#pragma once

#include <OpenMesh/Core/Geometry/VectorT.hh>

#include "infrastructure/ModelObject.h"

class PolygonalLasso : public ModelObject
{
    Q_OBJECT

    Q_PROPERTY(std::vector<OpenMesh::Vec3f> LassoPoints READ getPoints)

public:
    PolygonalLasso();
    virtual ~PolygonalLasso();

    void insertPoint(const OpenMesh::Vec3f& _point);

    std::vector<OpenMesh::Vec3f> getPoints() const;

private:
    std::vector<OpenMesh::Vec3f> mLassoPoints;
};
