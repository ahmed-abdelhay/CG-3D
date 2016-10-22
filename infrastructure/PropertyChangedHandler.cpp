#include "PropertyChangedHandler.h"
#include "ContextChangedPublisher.h"

PropertyChangedHandler::PropertyChangedHandler()
{}

PropertyChangedHandler::~PropertyChangedHandler()
{}

void PropertyChangedHandler::subscribePropertyChangedOnType(const std::string &_objectType, ContextChangedPublisher *_publisher)
{
    _publisher->attach(_objectType, this);
}

void PropertyChangedHandler::unsubscribePropertyChangedOnType(const std::string &_objectType, ContextChangedPublisher *_publisher)
{
    _publisher->detach(_objectType, this);
}
