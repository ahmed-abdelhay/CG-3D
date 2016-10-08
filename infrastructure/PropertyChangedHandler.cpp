#include "PropertyChangedHandler.h"
#include "ContextChangedPublisher.h"

PropertyChangedHandler::PropertyChangedHandler()
{}

PropertyChangedHandler::~PropertyChangedHandler()
{}

void PropertyChangedHandler::subscribePropertyChangedOnType(const std::string &fObjectType, ContextChangedPublisher *fPublisher)
{
    fPublisher->attach(fObjectType, this);
}

void PropertyChangedHandler::unsubscribePropertyChangedOnType(const std::string &fObjectType, ContextChangedPublisher *fPublisher)
{
    fPublisher->detach(fObjectType, this);
}
