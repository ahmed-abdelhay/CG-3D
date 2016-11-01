#include "ContextChangedPublisher.h"
#include "ContainerChangedHandler.h"
#include "PropertyChangedHandler.h"
#include "Type.h"

ContextChangedPublisher::ContextChangedPublisher()
    : QObject()
{}

ContextChangedPublisher::~ContextChangedPublisher()
{}

void ContextChangedPublisher::attach(ContainerChangedHandler *_containerChangedHandler)
{
    mContainerChangedHandlers.push_back(_containerChangedHandler);
}

void ContextChangedPublisher::detach(ContainerChangedHandler *_containerChangedHandler)
{
    mContainerChangedHandlers.erase(std::remove(mContainerChangedHandlers.begin(), mContainerChangedHandlers.end(), _containerChangedHandler), mContainerChangedHandlers.end());
}

void ContextChangedPublisher::attach(const std::string &_modelObjectType, PropertyChangedHandler *_propertyChangedHandler)
{
    if (mModelObjectTypeToHandlersMap.find(_modelObjectType) == mModelObjectTypeToHandlersMap.end())
    {
        std::vector<PropertyChangedHandler*> handlersVector{_propertyChangedHandler};
        auto modelObjectObserversPair = std::make_pair(_modelObjectType, handlersVector);
        mModelObjectTypeToHandlersMap.insert(modelObjectObserversPair);
    }
    else
    {
        mModelObjectTypeToHandlersMap[_modelObjectType].push_back(_propertyChangedHandler);
    }
}

void ContextChangedPublisher::detach(const std::string &_modelObjectType, PropertyChangedHandler *_propertyChangedHandler)
{
    auto handlersVector = mModelObjectTypeToHandlersMap[_modelObjectType];
    handlersVector.erase(std::remove(handlersVector.begin(), handlersVector.end(), _propertyChangedHandler), handlersVector.end());
}

void ContextChangedPublisher::publishContainerChanged(const std::shared_ptr<Type> &_object, ContainerChangeType _changeType) const
{
    for (const auto& observer : mContainerChangedHandlers)
        observer->notifyContainerChanged(_object, _changeType);
}

void ContextChangedPublisher::publishPropertyChanged(Type *_sourceObject, const std::string &_propertyType)
{
    std::string objectType = _sourceObject->metaObject()->className();
    for (auto handler : mModelObjectTypeToHandlersMap[objectType])
        handler->propertyChanged(_sourceObject, _propertyType);
}
