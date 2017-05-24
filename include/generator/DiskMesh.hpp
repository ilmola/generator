// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_DISKMESH_HPP
#define GENERATOR_DISKMESH_HPP


#include "AxisSwapMesh.hpp"
#include "LatheMesh.hpp"
#include "LineShape.hpp"


namespace generator {


/// A circular disk centered at origin on the xy-plane.
/// @image html DiskMesh.svg
class DiskMesh
{
private:

	using Impl = AxisSwapMesh<LatheMesh<LineShape>>;
	Impl axisSwapMesh_;

public:

	/// @param radius Outer radius of the disk on the xy-plane.
	/// @param innerRadius radius of the inner circle on the xy-plane.
	/// @param slices Number of subdivisions around the z-axis.
	/// @param rings Number of subdivisions along the radius.
	/// @param start Counterclockwise angle relative to the x-axis
	/// @param sweep Counterclockwise angle.
	DiskMesh(
		double radius = 1.0,
		double innerRadius = 0.0,
		int slices = 32,
		int rings = 4,
		double start = 0.0,
		double sweep = gml::radians(360.0)
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return axisSwapMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return axisSwapMesh_.vertices(); }

};


}

#endif
