#include "Type.h"

size_t Type::UID = 0;

Type::Type()
    : QObject()
{
    mUID = UID++;
}

size_t Type::getID()
{
    return mUID;
}
