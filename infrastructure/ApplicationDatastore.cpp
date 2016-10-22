#include "ApplicationDatastore.h"
#include "Type.h"
#include "ModelObject.h"

ApplicationDatastore::ApplicationDatastore()
    :QObject()
{}

void ApplicationDatastore::insertObject(const std::shared_ptr<Type> &_object)
{
    mDataStore.emplace_back(_object);
    emit containerChanged(_object, ContainerChangeType::OBJECT_ADDED);

    if(auto modelObject = dynamic_cast<ModelObject*>(_object.get()))
    {
        connect(modelObject,
                SIGNAL(propertyChanged(Type*,std::string)),
                this,
                SIGNAL(modelObjectPropertyChanged(Type*,std::string)));
    }
}

void ApplicationDatastore::removeObject(const std::shared_ptr<Type> &_object)
{
    // use the swap and pop method instrad of using erase for performance optimization
    auto itr = std::find(mDataStore.begin(), mDataStore.end(), _object);
    if (itr != mDataStore.end())
    {
        emit containerChanged(_object, ContainerChangeType::OBJECT_REMOVED);
        auto index = std::distance(mDataStore.begin(), itr) - 1;
        std::swap(mDataStore[index], mDataStore.back());
        mDataStore.pop_back();
    }
}

void ApplicationDatastore::removeObject(size_t _objectID)
{
    for(const auto& object : mDataStore)
    {
        if (object->getID() == _objectID)
        {
            removeObject(object);
            return;
        }
    }
}

void ApplicationDatastore::clearDataStore()
{
    for (auto& object : mDataStore)
        removeObject(object);
}

std::vector<std::shared_ptr<Type>> ApplicationDatastore::getAllObjectOfType(const std::string &_type)
{
    std::vector<std::shared_ptr<Type>> objects;
    for (const auto& object : mDataStore)
    {
        if (object->metaObject()->className() == _type)
            objects.push_back(object);
    }
    return objects;
}
