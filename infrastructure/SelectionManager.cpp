#include "SelectionManager.h"
#include "Type.h"

SelectionManager::SelectionManager()
{}

SelectionManager::~SelectionManager()
{}

void SelectionManager::setSelectedObject(std::string _objectType, std::shared_ptr<Type> _selectedObject)
{
    std::weak_ptr<Type> selectedObject = _selectedObject;
    mSelectionMap[_objectType] = selectedObject;
}
