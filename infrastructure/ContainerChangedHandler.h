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

    virtual void subscribeToContainerChanged(ContextChangedPublisher* fSubject);
    virtual void unsubscribeToContainerChanged(ContextChangedPublisher* fSubject);

    virtual void notifyContainerChanged(const std::shared_ptr<Type>& fObject, ContainerChangeType fChangeType) = 0;
};
