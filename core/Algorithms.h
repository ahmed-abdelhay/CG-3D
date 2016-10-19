#pragma once

#include <vector>
#include <OpenMesh/Core/Geometry/VectorT.hh>
#include <OpenMesh/Core/Geometry/MathDefs.hh>
class Algorithms
{
public:
    // this implementation is based on Graphics Gems

    // area is +ve if the polygon vertcies order is counter clockwise
    // -ve if the order is clockwise
    template <typename T>
    static T calculatePolygonArea(const std::vector<OpenMesh::VectorT<T, 2>>& fPolygon);

    template <typename T>
    static OpenMesh::VectorT<T, 2> calculatePolygonCentroid(const std::vector<OpenMesh::VectorT<T, 2>>& fPolygon);

};

template <typename T>
T Algorithms::calculatePolygonArea(const std::vector<OpenMesh::VectorT<T, 2>> &fPolygon)
{
    auto pointsCount = fPolygon.size();

    assert(pointsCount >= 3);

    T area = 0;
    for (int i = 0; i < pointsCount; ++i)
    {
        int nextIndex = (i + 1) % pointsCount;
        area += fPolygon[i][0] * fPolygon[nextIndex][1] - fPolygon[nextIndex][0] * fPolygon[i][1];
    }

    area *= 0.5;
    return area;
}

template <typename T>
OpenMesh::VectorT<T, 2> Algorithms::calculatePolygonCentroid(const std::vector<OpenMesh::VectorT<T, 2> > &fPolygon)
{
    T firstMomentX = 0;
    T firstMomentY = 0;
    T area = 0;

    auto pointsCount = fPolygon.size();

    assert(pointsCount >= 3);

    for (int i = 0; i < pointsCount; ++i)
    {
        int nextIndex = (i + 1) % pointsCount;
        T a = fPolygon[i][0] * fPolygon[nextIndex][1] - fPolygon[nextIndex][0] * fPolygon[i][1];
        area += a;
        firstMomentX += (fPolygon[i][0] + fPolygon[nextIndex][0]) * a;
        firstMomentY += (fPolygon[i][1] + fPolygon[nextIndex][1]) * a;
    }

    OpenMesh::VectorT<T, 2> centroid;
    if (!OpenMesh::is_zero(area))
    {
        centroid[0] = firstMomentX / (3 * area);
        centroid[1] = firstMomentY / (3 * area);
    }

    return centroid;
}
