#include "ContainerChangedHandler.h"
#include "ContextChangedPublisher.h"

ContainerChangedHandler::ContainerChangedHandler()
{}

ContainerChangedHandler::~ContainerChangedHandler()
{}

void ContainerChangedHandler::subscribeToContainerChanged(ContextChangedPublisher *fSubject)
{
    fSubject->attach(this);
}

void ContainerChangedHandler::unsubscribeToContainerChanged(ContextChangedPublisher *fSubject)
{
    fSubject->detach(this);
}
