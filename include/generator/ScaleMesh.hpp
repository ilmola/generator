// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_SCALEMESH_HPP
#define GENERATOR_SCALEMESH_HPP

#include "TransformMesh.hpp"


namespace generator {


/// Scales a mesh (keeps normals unit length)
template <typename Mesh>
class ScaleMesh
{
private:

	using Impl = TransformMesh<Mesh>;
	Impl transformMesh_;

public:

	/// @param mesh Source data mesh.
	/// @param scale Scale factors. Must not be zero!
	ScaleMesh(Mesh mesh, const gml::dvec3& scale) :
		transformMesh_{
			std::move(mesh),
			[scale] (MeshVertex& value) {
				value.position *= scale;
				value.normal = normalize(scale * value.normal);
			}
		}
	{ }

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return transformMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformMesh_.vertices(); }

};


template <typename Mesh>
ScaleMesh<Mesh> scaleMesh(Mesh mesh, const gml::dvec3& delta) {
	return ScaleMesh<Mesh>{std::move(mesh), delta};
}

}

#endif

