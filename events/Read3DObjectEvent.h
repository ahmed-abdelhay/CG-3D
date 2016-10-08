#pragma once

#include <string>

#include "infrastructure/Event.h"

class Read3DObjectEvent : public Event
{
public:
    Read3DObjectEvent();

    std::string meshFileName;
};
