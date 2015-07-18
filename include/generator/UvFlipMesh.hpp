// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_UVFLIPMESH_HPP
#define GENERATOR_UVFLIPMESH_HPP

#include "TransformMesh.hpp"


namespace generator {


/// Flips texture coordinate axis directions.
template <typename Mesh>
class UvFlipMesh :
	private TransformMesh<Mesh>
{
public:

	/// @param mesh Source data mesh.
	/// @param u Flip u
	/// @param v Flip v
	UvFlipMesh(Mesh mesh, bool u, bool v) :
		TransformMesh<Mesh>{
			std::move(mesh),
			[u, v] (MeshVertex& vertex) {
				if (u) vertex.texCoord[0] = 1.0 - vertex.texCoord[0];
				if (v) vertex.texCoord[1] = 1.0 - vertex.texCoord[1];
			}
		}
	{ }

	using TransformMesh<Mesh>::triangles;

	using TransformMesh<Mesh>::vertices;

};


template <typename Mesh>
UvFlipMesh<Mesh> uvFlipMesh(Mesh mesh) {
	return UvFlipMesh<Mesh>{std::move(mesh)};
}


}


#endif

