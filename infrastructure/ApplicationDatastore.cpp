#include "ApplicationDatastore.h"
#include "Type.h"
#include "ModelObject.h"

ApplicationDatastore::ApplicationDatastore()
    :QObject()
{}

void ApplicationDatastore::insertObject(const std::shared_ptr<Type> &fObject)
{
    mDataStore.emplace_back(fObject);
    emit containerChanged(fObject, ContainerChangeType::OBJECT_ADDED);

    if(auto modelObject = dynamic_cast<ModelObject*>(fObject.get()))
    {
        connect(modelObject,
                SIGNAL(propertyChanged(Type*,std::string)),
                this,
                SIGNAL(modelObjectPropertyChanged(Type*,std::string)));
    }
}

void ApplicationDatastore::removeObject(const std::shared_ptr<Type> &fObject)
{
    // use the swap and pop method instrad of using erase for performance optimization
    auto itr = std::find(mDataStore.begin(), mDataStore.end(), fObject);
    if (itr != mDataStore.end())
    {
        auto index = std::distance(mDataStore.begin(), itr) - 1;
        std::swap(mDataStore[index], mDataStore.back());
        mDataStore.pop_back();
        emit containerChanged(fObject, ContainerChangeType::OBJECT_REMOVED);
    }
}

void ApplicationDatastore::clearDataStore()
{
    for (auto& object : mDataStore)
        removeObject(object);
}
