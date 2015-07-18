// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_UVSWAPMESH_HPP
#define GENERATOR_UVSWAPMESH_HPP

#include "TransformMesh.hpp"


namespace generator {


/// Swaps the texture coordinates axis u and v.
template <typename Mesh>
class UvSwapMesh :
	private TransformMesh<Mesh>
{
public:

	/// @param mesh Source data mesh
	UvSwapMesh(Mesh mesh) :
		TransformMesh<Mesh>{
			std::move(mesh),
			[] (MeshVertex& vertex) {
				std::swap(vertex.texCoord[0], vertex.texCoord[1]);
			}
		}
	{ }

	using TransformMesh<Mesh>::triangles;

	using TransformMesh<Mesh>::vertices;

};

template <typename Mesh>
UvSwapMesh<Mesh> uvSwapMesh(Mesh mesh) {
	return UvSwapMesh<Mesh>{std::move(mesh)};
}


}


#endif

