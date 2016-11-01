#pragma once

#include <infrastructure/Event.h>

#include <memory>

#include <QColor>

class Type;
class Change3DObjectColorEvent : public Event
{
public:
    Change3DObjectColorEvent();

    std::shared_ptr<Type> object;
    QColor color;
};
