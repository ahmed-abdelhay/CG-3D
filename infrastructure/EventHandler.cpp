#include "EventHandler.h"
#include "EventPublisher.h"

EventHandler::EventHandler()
{}

EventHandler::~EventHandler()
{}

void EventHandler::subscribeToEvents(EventPublisher *fSubject)
{
    fSubject->attach(this);
}

void EventHandler::unsubscribeToEvents(EventPublisher *fSubject)
{
    fSubject->detach(this);
}
