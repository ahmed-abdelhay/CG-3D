#pragma once

#include <string>
#include <memory>

#include "infrastructure/Event.h"
#include "modelObjects/ThreeDObject.h"

class Write3DObjectEvent : public Event
{
public:
    Write3DObjectEvent();

    std::string meshFileName;
    std::shared_ptr<ThreeDObject> object;
};
