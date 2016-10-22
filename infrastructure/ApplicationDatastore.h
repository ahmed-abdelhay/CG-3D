#pragma once

#include <QObject>
#include <vector>
#include <string>
#include <memory>

#include "Common.h"

class Type;

class ApplicationDatastore : public QObject
{
    Q_OBJECT
public:
    ApplicationDatastore();
    virtual ~ApplicationDatastore(){}

    void insertObject(const std::shared_ptr<Type>& _object);
    void removeObject(const std::shared_ptr<Type>& _object);
    void removeObject(size_t _objectID);

    void clearDataStore();

    std::vector<std::shared_ptr<Type>> getAllObjectOfType(const std::string& _type);

signals:
    void containerChanged(const std::shared_ptr<Type>& _object, ContainerChangeType  _changeType);
    void modelObjectPropertyChanged(Type* _object, const std::string& _propertyType);

private:
    std::vector<std::shared_ptr<Type>> mDataStore;
};
