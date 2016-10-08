#pragma once

#include "Type.h"

// a base class for all the model objects
class ModelObject : public Type
{
    Q_OBJECT
public:
    ModelObject();
    virtual ~ModelObject();

signals:
    // this signal will be emitted if the property of the object changed
    void propertyChanged(Type* fSourceObject, const std::string& fPropertyName);
};
