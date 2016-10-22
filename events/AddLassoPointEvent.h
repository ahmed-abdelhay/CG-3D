#pragma once

#include<QPoint>
#include "infrastructure/Event.h"

class AddLassoPointEvent : public Event
{
public:
    AddLassoPointEvent();
    QPoint lassoPoint;
};
