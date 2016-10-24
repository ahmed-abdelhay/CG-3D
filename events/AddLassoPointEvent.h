#pragma once

#include <OpenMesh/Core/Geometry/VectorT.hh>
#include "infrastructure/Event.h"

class AddLassoPointEvent : public Event
{
public:
    AddLassoPointEvent();
    OpenMesh::Vec3f lassoPoint;
};
