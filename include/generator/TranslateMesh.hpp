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
class TranslateMesh
{
private:

	using Impl = TransformMesh<Mesh>;
	Impl transformMesh_;

public:

	/// @param mesh Source data mesh.
	/// @param delta Amount to increment vertex positions.
	TranslateMesh(Mesh mesh, const gml::dvec3& delta) :
		transformMesh_{
			std::move(mesh),
			[delta] (MeshVertex& value) { value.position += delta; }
		}
	{ }

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return transformMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformMesh_.vertices(); }

};


template <typename Mesh>
TranslateMesh<Mesh> translateMesh(Mesh mesh, const gml::dvec3& delta) {
	return TranslateMesh<Mesh>{std::move(mesh), delta};
}

}

#endif
