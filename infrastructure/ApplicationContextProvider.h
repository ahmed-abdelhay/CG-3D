#pragma once

#include "Type.h"

class ApplicationContext;

// a base class for all the classes that whises to use the context
class ApplicationContextProvider : public Type
{
public:
    ApplicationContextProvider();
    virtual ~ApplicationContextProvider();

    virtual void setContext(ApplicationContext* fContext) = 0;
    ApplicationContext* context();

protected:
    ApplicationContext* mContext;
};
