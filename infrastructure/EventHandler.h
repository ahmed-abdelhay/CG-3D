#pragma once

#include <memory>

class Event;
class EventPublisher;

// a base class for all the classes that wish to listen to events
class EventHandler
{
public:
    EventHandler();

    virtual ~EventHandler();

    virtual void notify(const std::shared_ptr<Event>& _event) = 0;

    virtual void subscribeToEvents(EventPublisher* _subject);
    virtual void unsubscribeToEvents(EventPublisher* _subject);
};
