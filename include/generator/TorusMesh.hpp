// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_TORUS_HPP
#define GENERATOR_TORUS_HPP

#include "AxisSwapMesh.hpp"
#include "CircleShape.hpp"
#include "LatheMesh.hpp"
#include "TranslateShape.hpp"


namespace generator {


/// Torus centered at origin on the xy-plane.
/// @image html TorusMesh.svg
class TorusMesh
{
private:

	using Impl = AxisSwapMesh<LatheMesh<TranslateShape<CircleShape>>>;
	Impl axisSwapMesh_;

public:

	/// @param minor Radius of the minor (inner) ring
	/// @param major Radius of the major (outer) ring
	/// @param slices Subdivisions around the minor ring
	/// @param segments Subdivisions around the major ring
	/// @param minorStart Counterclockwise angle relative to the xy-plane.
	/// @param minorSweep Counterclockwise angle around the circle.
	/// @param majorStart Counterclockwise angle around the z-axis relative to the x-axis.
	/// @param majorSweep Counterclockwise angle around the z-axis.
	TorusMesh(
		double minor = 0.25,
		double major = 1.0,
		int slices = 16,
		int segments = 32,
		double minorStart = 0.0,
		double minorSweep = gml::radians(360.0),
		double majorStart = 0.0,
		double majorSweep = gml::radians(360.0)
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return axisSwapMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return axisSwapMesh_.vertices(); }

};


}


#endif
