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
class TorusKnotMesh :
	private ExtrudeMesh<CircleShape, KnotPath>
{
public:

	/// @param slices Number subdivisions around the circle.
	/// @param segments Number of subdivisions around the path.
	TorusKnotMesh(
		int p = 2,
		int q = 3,
		unsigned slices = 8u,
		unsigned segments = 96u
	);

	using ExtrudeMesh<CircleShape, KnotPath>::triangles;

	using ExtrudeMesh<CircleShape, KnotPath>::vertices;

};

}



#endif
