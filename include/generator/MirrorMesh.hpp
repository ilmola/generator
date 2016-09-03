// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_MIRRORMESH_HPP
#define GENERATOR_MIRRORMESH_HPP


#include "Axis.hpp"
#include "AxisFlipMesh.hpp"
#include "MergeMesh.hpp"


namespace generator {


/// Duplicates the mesh by mirrorring it along an axis.
template <typename Mesh>
class MirrorMesh
{
private:

	using Impl = MergeMesh<Mesh, AxisFlipMesh<Mesh>>;
	Impl mergeMesh_;

public:

	/// @param mesh Source data mesh.
	/// @param axis The axis to mirror along.
	MirrorMesh(Mesh mesh, Axis axis) :
		mergeMesh_{
			mesh, {mesh, axis == Axis::X, axis == Axis::Y, axis == Axis::Z}
		}
	{ }

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return mergeMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return mergeMesh_.vertices(); }

};


template <typename Mesh>
MirrorMesh<Mesh> mirrorMesh(Mesh mesh) {
	return MirrorMesh<Mesh>{std::move(mesh)};
}

}

#endif
