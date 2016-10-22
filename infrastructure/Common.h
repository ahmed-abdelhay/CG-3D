#pragma once

#include <string>

enum class ContainerChangeType
{
    OBJECT_ADDED,
    OBJECT_REMOVED,
};

// model objects names
static const std::string ThreeDObjectType = "ThreeDObject";
static const std::string PolygonalLassoType = "PolygonalLasso";

// properties names
static const std::string ColorType = "Color";
static const std::string NameType = "Name";
static const std::string MeshType = "Mesh";
static const std::string LassoPointsType = "LassoPoints";

