#pragma once

#include "infrastructure/EventPublisher.h"
#include "infrastructure/ContextChangedPublisher.h"

#include <memory>

class ApplicationDatastore;
class SelectionManager;
class Type;

class ApplicationContext : public EventPublisher, public ContextChangedPublisher
{
public:
    ApplicationContext();
    virtual ~ApplicationContext();

    ApplicationDatastore *dataStore();

    SelectionManager *selectionManager();

private:
    std::unique_ptr<ApplicationDatastore> mDataStore;
    std::unique_ptr<SelectionManager> mSelectionManager;
};
