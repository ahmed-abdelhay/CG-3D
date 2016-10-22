#pragma once

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <vector>

typedef OpenMesh::TriMesh_ArrayKernelT<OpenMesh::DefaultTraits>  TriangleMesh;

class TriMesh : public TriangleMesh
{
public:
    TriMesh();
    virtual ~TriMesh();

    void clearFaceSelection();
    void setFaceSelectionState(const OpenMesh::FaceHandle _fh, bool _selectionState);

    std::vector<OpenMesh::FaceHandle> getSelectedFaces();

private:
    OpenMesh::FPropHandleT<bool> mFaceSelectionProperty;
};
