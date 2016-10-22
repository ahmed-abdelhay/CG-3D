#pragma once

class ApplicationContext;

// a base class for all the classes that whises to use the context
class ApplicationContextProvider
{
public:
    ApplicationContextProvider();
    virtual ~ApplicationContextProvider();

    virtual void setContext(ApplicationContext* _context) = 0;
    ApplicationContext* context();

protected:
    ApplicationContext* mContext;
};
