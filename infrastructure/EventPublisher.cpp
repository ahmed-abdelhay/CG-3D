#include "EventPublisher.h"
#include "EventHandler.h"
#include "Event.h"

#include <algorithm>

EventPublisher::EventPublisher()
{}

EventPublisher::~EventPublisher()
{}

void EventPublisher::attach(EventHandler *fEventHandler)
{
    mObservers.push_back(fEventHandler);
}

void EventPublisher::detach(EventHandler *fEventHandler)
{
    mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), fEventHandler), mObservers.end());
}

void EventPublisher::publish(const std::shared_ptr<Event>& fEvent) const
{
    for(const auto& observer : mObservers)
        observer->notify(fEvent);
}
