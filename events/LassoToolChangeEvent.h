#pragma once

#include "infrastructure/Event.h"

class LassoToolChangeEvent : public Event
{
public:
    enum class LassoToolType
    {
        POLYGONAL_LASSO_TOOL,
    };

    LassoToolChangeEvent();

    bool toolState;
    LassoToolType lassoToolType;
};
