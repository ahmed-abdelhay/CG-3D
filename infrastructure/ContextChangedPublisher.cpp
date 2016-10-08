#include "ContextChangedPublisher.h"
#include "ContainerChangedHandler.h"
#include "PropertyChangedHandler.h"
#include "Type.h"

ContextChangedPublisher::ContextChangedPublisher()
    : QObject()
{}

ContextChangedPublisher::~ContextChangedPublisher()
{}

void ContextChangedPublisher::attach(ContainerChangedHandler *fContainerChangedHandler)
{
    mContainerChangedHandlers.push_back(fContainerChangedHandler);
}

void ContextChangedPublisher::detach(ContainerChangedHandler *fContainerChangedHandler)
{
    mContainerChangedHandlers.erase(std::remove(mContainerChangedHandlers.begin(), mContainerChangedHandlers.end(), fContainerChangedHandler), mContainerChangedHandlers.end());
}

void ContextChangedPublisher::attach(const std::string &fModelObjectType, PropertyChangedHandler *fPropertyChangedHandler)
{
    if (mModelObjectTypeToHandlersMap.find(fModelObjectType) == mModelObjectTypeToHandlersMap.end())
    {
        std::vector<PropertyChangedHandler*> handlersVector{fPropertyChangedHandler};
        auto modelObjectObserversPair = std::make_pair(fModelObjectType, handlersVector);
        mModelObjectTypeToHandlersMap.insert(modelObjectObserversPair);
    }
    else
    {
        mModelObjectTypeToHandlersMap[fModelObjectType].push_back(fPropertyChangedHandler);
    }
}

void ContextChangedPublisher::detach(const std::string &fModelObjectType, PropertyChangedHandler *fPropertyChangedHandler)
{
    auto handlersVector = mModelObjectTypeToHandlersMap[fModelObjectType];
    handlersVector.erase(std::remove(handlersVector.begin(), handlersVector.end(), fPropertyChangedHandler), handlersVector.end());
}

void ContextChangedPublisher::publishContainerChanged(const std::shared_ptr<Type> &fObject, ContainerChangeType fChangeType) const
{
    for (const auto& observer : mContainerChangedHandlers)
        observer->notifyContainerChanged(fObject, fChangeType);
}



void ContextChangedPublisher::publishPropertyChanged(Type *fSourceObject, const std::string &fPropertyType)
{
    std::string objectType = fSourceObject->metaObject()->className();
    for (auto handler : mModelObjectTypeToHandlersMap[objectType])
        handler->propertyChanged(fSourceObject, fPropertyType);
}
