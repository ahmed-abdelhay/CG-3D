#include "EventHandler.h"
#include "EventPublisher.h"

EventHandler::EventHandler()
{}

EventHandler::~EventHandler()
{}

void EventHandler::subscribeToEvents(EventPublisher *_subject)
{
    _subject->attach(this);
}

void EventHandler::unsubscribeToEvents(EventPublisher *_subject)
{
    _subject->detach(this);
}
