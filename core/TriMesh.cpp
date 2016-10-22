#include "TriMesh.h"


TriMesh::TriMesh()
{
    add_property(mFaceSelectionProperty);
    clearFaceSelection();
}

TriMesh::~TriMesh()
{
    remove_property(mFaceSelectionProperty);
}

void TriMesh::clearFaceSelection()
{
    for (const auto& fh : faces())
        property(mFaceSelectionProperty, fh) = false;
}

void TriMesh::setFaceSelectionState(const OpenMesh::FaceHandle _fh, bool _selectionState)
{
    property(mFaceSelectionProperty, _fh) = _selectionState;
}

std::vector<OpenMesh::FaceHandle> TriMesh::getSelectedFaces()
{
    std::vector<OpenMesh::FaceHandle> selectedFaces;
    for (const auto& fh : faces())
       if (property(mFaceSelectionProperty, fh))
           selectedFaces.push_back(fh);
    return selectedFaces;
}
