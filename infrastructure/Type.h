#pragma once

#include <QObject>

// the base type of all the objects in the application that whises to use
// the reflection layer
// it also supplies each object with a unique ID

class Type : public QObject
{
    Q_OBJECT
public:
    Type();
    virtual ~Type(){}

    size_t getID();

private:
    size_t mUID; // unique ID for the object
    static size_t UID;
};
