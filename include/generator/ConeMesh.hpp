// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_CONEMESH_HPP
#define GENERATOR_CONEMESH_HPP

#include "AxisSwapMesh.hpp"
#include "LatheMesh.hpp"
#include "LineShape.hpp"
#include "UvFlipMesh.hpp"


namespace generator {



/// A cone centered at origin tip pointing towards z-axis.
/// @image html ConeMesh.svg
class ConeMesh
{
private:

	using Impl = AxisSwapMesh<LatheMesh<LineShape>>;
	Impl axisSwapMesh_;

public:

	///@param radius Radius of the negative z end on the xy-plane.
	///@param size Half of the length of the cylinder along the z-axis.
	///@param slices Number of subdivisions around the z-axis.
	///@param segments Number subdivisions along the z-axis.
	///@param start Counterclockwise angle around the z-axis relative to the x-axis.
	///@param sweep Counterclockwise angle around the z-axis.
	ConeMesh(
		double radius = 1.0,
		double size = 1.0,
		int slices = 32,
		int segments = 8,
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
