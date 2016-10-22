#pragma once

#include <string>

class Type;
class ContextChangedPublisher;

class PropertyChangedHandler
{
public:
    PropertyChangedHandler();
    virtual ~PropertyChangedHandler();

    void subscribePropertyChangedOnType(const std::string& _objectType, ContextChangedPublisher* _publisher);
    void unsubscribePropertyChangedOnType(const std::string& _objectType, ContextChangedPublisher* _publisher);

    virtual void propertyChanged(Type* _source, const std::string& _propertyName) = 0;
};
