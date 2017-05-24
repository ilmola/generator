// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_TORUSKNOTMESH_HPP
#define GENERATOR_TORUSKNOTMESH_HPP

#include "CircleShape.hpp"
#include "ExtrudeMesh.hpp"
#include "KnotPath.hpp"

namespace generator {


/// A Circle extruded along a knot path.
/// @image html TorusKnotMesh.svg
class TorusKnotMesh
{
private:

	using Impl = ExtrudeMesh<CircleShape, KnotPath>;
	Impl extrudeMesh_;

public:

	/// @param slices Number subdivisions around the circle.
	/// @param segments Number of subdivisions around the path.
	TorusKnotMesh(
		int p = 2,
		int q = 3,
		int slices = 8,
		int segments = 96
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return extrudeMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return extrudeMesh_.vertices(); }

};

}



#endif
