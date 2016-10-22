#include "EventPublisher.h"
#include "EventHandler.h"
#include "Event.h"

#include <algorithm>

EventPublisher::EventPublisher()
{}

EventPublisher::~EventPublisher()
{}

void EventPublisher::attach(EventHandler *_eventHandler)
{
    mObservers.push_back(_eventHandler);
}

void EventPublisher::detach(EventHandler *_eventHandler)
{
    mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), _eventHandler), mObservers.end());
}

void EventPublisher::publish(const std::shared_ptr<Event>& _event) const
{
    for(const auto& observer : mObservers)
        observer->notify(_event);
}
