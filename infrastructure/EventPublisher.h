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

    void attach(EventHandler* fEventHandler);
    void detach(EventHandler* fEventHandler);

    virtual void publish(const std::shared_ptr<Event> &fEvent) const;

protected:
    std::vector<EventHandler*> mObservers;
};
