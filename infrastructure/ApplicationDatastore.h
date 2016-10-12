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

    void insertObject(const std::shared_ptr<Type>& fObject);
    void removeObject(const std::shared_ptr<Type>& fObject);
    void removeObject(size_t fObjectID);

    void clearDataStore();

signals:
    void containerChanged(const std::shared_ptr<Type>& fObject, ContainerChangeType fChangeType);
    void modelObjectPropertyChanged(Type* fObject, const std::string& fPropertyType);

private:
    std::vector<std::shared_ptr<Type>> mDataStore;
};
