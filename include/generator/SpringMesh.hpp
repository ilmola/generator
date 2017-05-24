// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_SPRINGMESH_HPP
#define GENERATOR_SPRINGMESH_HPP

#include "CircleShape.hpp"
#include "ExtrudeMesh.hpp"
#include "HelixPath.hpp"

namespace generator {


/// A spring aligned along the z-axis winding counterclockwise
/// @image html SpringMesh.svg
class SpringMesh
{
private:

	using Impl = ExtrudeMesh<CircleShape, HelixPath>;
	Impl extrudeMesh_;

public:

	/// @param minor Radius of the spring it self.
	/// @param major Radius from the z-axis
	/// @param size Half of the length along the z-axis.
	/// @param slices Subdivisions around the spring.
	/// @param segments Subdivisions along the path.
	/// @param majorStart Counterclockwise angle around the z-axis relative to the x-axis.
	/// @param majorSweep Counterclockwise angle arounf the z-axis.
	SpringMesh(
		double minor = 0.25,
		double major = 1.0,
		double size = 1.0,
		int slices = 8,
		int segments = 32,
		double minorStart = 0.0,
		double minorSweep = gml::radians(360.0),
		double majorStart = 0.0,
		double majorSweep = gml::radians(720.0)
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return extrudeMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return extrudeMesh_.vertices(); }

};

}



#endif
