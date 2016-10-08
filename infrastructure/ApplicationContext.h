#pragma once

#include "EventPublisher.h"
#include "ContextChangedPublisher.h"

#include <memory>

class ApplicationDatastore;

class ApplicationContext : public EventPublisher, public ContextChangedPublisher
{
public:
    ApplicationContext();
    virtual ~ApplicationContext();

    ApplicationDatastore *dataStore();

private:
    std::unique_ptr<ApplicationDatastore> mDataStore;
};
