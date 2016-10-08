#include "ApplicationContext.h"
#include "ApplicationDatastore.h"

ApplicationContext::ApplicationContext()
    :mDataStore(new ApplicationDatastore())
{
    connect(mDataStore.get(), SIGNAL(ApplicationDatastore::containerChanged), this, SLOT(publishContainerChanged));
    connect(mDataStore.get(), SIGNAL(ApplicationDatastore::propertyChanged), this, SLOT(publishContainerChanged));
}

ApplicationContext::~ApplicationContext()
{}

ApplicationDatastore *ApplicationContext::dataStore()
{
    return mDataStore.get();
}
