#pragma once

#include <infrastructure/Event.h>
#include <QColor>

class Type;
class Change3DObjectColorEvent : public Event
{
public:
    Change3DObjectColorEvent();

    Type* object;
    QColor color;
};
