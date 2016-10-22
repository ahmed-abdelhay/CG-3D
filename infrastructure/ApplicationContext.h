#pragma once

#include "EventPublisher.h"
#include "ContextChangedPublisher.h"

#include <memory>

class ApplicationDatastore;
class Type;

class ApplicationContext : public EventPublisher, public ContextChangedPublisher
{
public:
    ApplicationContext();
    virtual ~ApplicationContext();

    ApplicationDatastore *dataStore();

    // Selection managmenet logic (TODO add into a manager class later)
    void setSelectedObject(Type* _selectedObject);
    Type *getSelectedObject();

private:
    std::unique_ptr<ApplicationDatastore> mDataStore;
    Type* mSelectedObject;
};
