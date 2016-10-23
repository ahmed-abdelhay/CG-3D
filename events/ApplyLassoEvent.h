#pragma once

#include "infrastructure/Event.h"
#include <osg/Matrixd>

class ApplyLassoEvent : public Event
{
public:
    ApplyLassoEvent();

    osg::Matrixd viewMatrix;
    osg::Matrixd projectionMatrix;
};
