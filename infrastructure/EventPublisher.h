#pragma once

#include <vector>
#include <memory>

class EventHandler;
class Event;

class EventPublisher
{
public:
    EventPublisher();
    virtual ~EventPublisher();

    void attach(EventHandler* _eventHandler);
    void detach(EventHandler* _eventHandler);

    virtual void publish(const std::shared_ptr<Event> &_event) const;

protected:
    std::vector<EventHandler*> mObservers;
};
