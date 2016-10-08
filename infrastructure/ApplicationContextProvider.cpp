#include "ApplicationContextProvider.h"
#include "ApplicationContext.h"

ApplicationContextProvider::ApplicationContextProvider()
    : mContext(nullptr)
{}

ApplicationContextProvider::~ApplicationContextProvider()
{}

ApplicationContext *ApplicationContextProvider::context()
{
    return mContext;
}

