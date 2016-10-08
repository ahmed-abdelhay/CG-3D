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

    void attach(ContainerChangedHandler* fContainerChangedHandler);
    void detach(ContainerChangedHandler* fContainerChangedHandler);

    // attach a handler to a specific model object type
    void attach(const std::string& fModelObjectType, PropertyChangedHandler* fPropertyChangedHandler);
    // detach a handler from a specific model object type
    void detach(const std::string& fModelObjectType, PropertyChangedHandler* fPropertyChangedHandler);

public slots:
    void publishContainerChanged(const std::shared_ptr<Type>& fObject, ContainerChangeType fChangeType) const;
    void publishPropertyChanged(Type* fSourceObject, const std::string& fPropertyType);

protected:
    std::vector<ContainerChangedHandler*> mContainerChangedHandlers;
    std::map<std::string, std::vector<PropertyChangedHandler*>> mModelObjectTypeToHandlersMap;
};
