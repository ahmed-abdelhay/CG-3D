#include "ContainerChangedHandler.h"
#include "ContextChangedPublisher.h"

ContainerChangedHandler::ContainerChangedHandler()
{}

ContainerChangedHandler::~ContainerChangedHandler()
{}

void ContainerChangedHandler::subscribeToContainerChanged(ContextChangedPublisher *_subject)
{
    _subject->attach(this);
}

void ContainerChangedHandler::unsubscribeToContainerChanged(ContextChangedPublisher *_subject)
{
    _subject->detach(this);
}
