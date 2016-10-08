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

    virtual void notify(const std::shared_ptr<Event>& fEvent) = 0;

    virtual void subscribeToEvents(EventPublisher* fSubject);
    virtual void unsubscribeToEvents(EventPublisher* fSubject);
};
