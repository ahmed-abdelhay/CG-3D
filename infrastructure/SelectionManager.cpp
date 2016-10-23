#include "SelectionManager.h"
#include "Type.h"

SelectionManager::SelectionManager()
{}

SelectionManager::~SelectionManager()
{}

void SelectionManager::setSelectedObject(std::string _objectType, Type *_selectedObject)
{
    mSelectionMap[_objectType] = _selectedObject;
}
