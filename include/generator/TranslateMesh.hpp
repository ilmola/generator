// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_TRANSLATEMESH_HPP
#define GENERATOR_TRANSLATEMESH_HPP

#include "TransformMesh.hpp"


namespace generator {


/// Translates the position of each vertex by given amount.
template <typename Mesh>
class TranslateMesh :
	private TransformMesh<Mesh>
{
public:

	/// @param mesh Source data mesh.
	/// @param delta Amount to increment vertex positions.
	TranslateMesh(Mesh mesh, const gml::dvec3& delta) :
		TransformMesh<Mesh>{
			std::move(mesh),
			[delta] (MeshVertex& value) { value.position += delta; }
		}
	{ }

	using TransformMesh<Mesh>::triangles;

	using TransformMesh<Mesh>::vertices;

};


template <typename Mesh>
TranslateMesh<Mesh> translateMesh(Mesh mesh, const gml::dvec3& delta) {
	return TranslateMesh<Mesh>{std::move(mesh), delta};
}

}

#endif
