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

    void clearDataStore();

    // check for the datastore and if any object with type T
    // is available return it
    // else add a new instance of T into the datastore and return it
    // this function should be used with controllers and managers
    // and objects that should only exist once in the datastore
    //    template<typename T>
    //    std::shared_ptr<T> service();

signals:
    void containerChanged(const std::shared_ptr<Type>& fObject, ContainerChangeType fChangeType);
    void propertyChanged(Type* fObject, const std::string& fPropertyType);

private:
    std::vector<std::shared_ptr<Type>> mDataStore;
};

//template <typename T>
//std::shared_ptr<T> ApplicationDatastore::service()
//{
//    auto serviceName = T->metaObject()->className();
//    for (const auto& object : mDataStore)
//    {
//        if (object->metaObject()->className() == serviceName)
//            return object;
//    }
//    auto object = std::shared_ptr<T>(new T());
//    insertObject(object);
//    return object;
//}
