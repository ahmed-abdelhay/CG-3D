#pragma once

#include "ApplicationDatastore.h"
#include "Common.h"

#include <memory>


class ContextChangedPublisher;
class Type;

class ContainerChangedHandler
{
public:
    ContainerChangedHandler();
    virtual ~ContainerChangedHandler();

    virtual void subscribeToContainerChanged(ContextChangedPublisher* _subject);
    virtual void unsubscribeToContainerChanged(ContextChangedPublisher* _subject);

    virtual void notifyContainerChanged(const std::shared_ptr<Type>& _object, ContainerChangeType _changeType) = 0;
};
