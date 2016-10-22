#pragma once

#include <QObject>
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "Common.h"

class PropertyChangedHandler;
class ContainerChangedHandler;
class Type;

class ContextChangedPublisher : public QObject
{
    Q_OBJECT
public:
    ContextChangedPublisher();
    virtual ~ContextChangedPublisher();

    void attach(ContainerChangedHandler* _containerChangedHandler);
    void detach(ContainerChangedHandler* _containerChangedHandler);

    // attach a handler to a specific model object type
    void attach(const std::string& _modelObjectType, PropertyChangedHandler* _propertyChangedHandler);
    // detach a handler from a specific model object type
    void detach(const std::string& _modelObjectType, PropertyChangedHandler* _propertyChangedHandler);

public slots:
    void publishContainerChanged(const std::shared_ptr<Type>& _object, ContainerChangeType _changeType) const;
    void publishPropertyChanged(Type* _sourceObject, const std::string& _propertyType);

protected:
    std::vector<ContainerChangedHandler*> mContainerChangedHandlers;
    std::map<std::string, std::vector<PropertyChangedHandler*>> mModelObjectTypeToHandlersMap;
};
