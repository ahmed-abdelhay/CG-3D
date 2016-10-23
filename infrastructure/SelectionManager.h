#pragma once

#include <map>
#include <string>

class Type;

class SelectionManager
{
public:
    SelectionManager();
    ~SelectionManager();

    void setSelectedObject(std::string _objectType, Type* _selectedObject);

    template <typename T>
    T* getSelectedObject(std::string _objectType)
    {
        if (mSelectionMap.find(_objectType) != mSelectionMap.end())
            return dynamic_cast<T*>(mSelectionMap[_objectType]);
        return nullptr;
    }

private:
    // the class only supports single selection per type for now
    std::map<std::string, Type*> mSelectionMap;
};
