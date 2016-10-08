#pragma once

#include <string>

class Type;
class ContextChangedPublisher;

class PropertyChangedHandler
{
public:
    PropertyChangedHandler();
    virtual ~PropertyChangedHandler();

    void subscribePropertyChangedOnType(const std::string& fObjectType, ContextChangedPublisher* fPublisher);
    void unsubscribePropertyChangedOnType(const std::string& fObjectType, ContextChangedPublisher* fPublisher);

    virtual void propertyChanged(Type* fSource, const std::string& fPropertyName) = 0;
};
