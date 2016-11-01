#pragma once

#include <map>
#include <string>
#include <memory>

class Type;

class SelectionManager
{
public:
    SelectionManager();
    ~SelectionManager();

    void setSelectedObject(std::string _objectType, std::shared_ptr<Type> _selectedObject);

    template <typename T>
    std::shared_ptr<T> getSelectedObject(std::string _objectType)
    {
        if (mSelectionMap.find(_objectType) != mSelectionMap.end())
        {
            if (!mSelectionMap[_objectType].expired())
            return std::dynamic_pointer_cast<T>(mSelectionMap[_objectType].lock());
        }
        return nullptr;
    }

private:
    // the class only supports single selection per type for now
    std::map<std::string, std::weak_ptr<Type>> mSelectionMap;
};
