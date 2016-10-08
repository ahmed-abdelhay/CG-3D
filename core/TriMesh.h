#pragma once

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

typedef OpenMesh::TriMesh_ArrayKernelT<OpenMesh::DefaultTraits>  TriangleMesh;

class TriMesh : public TriangleMesh
{
public:
};
