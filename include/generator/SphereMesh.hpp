// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_SPHERE_HPP
#define GENERATOR_SPHERE_HPP

#include "AxisSwapMesh.hpp"
#include "CircleShape.hpp"
#include "LatheMesh.hpp"
#include "UvFlipMesh.hpp"


namespace generator {



/// A sphere of the given radius centered around the origin.
/// Subdivided around the z-axis in slices and along the z-axis in segments.
/// @image html SphereMesh.svg
class SphereMesh
{
private:

	using Impl = AxisSwapMesh<LatheMesh<CircleShape>>;
	Impl axisSwapMesh_;

public:

	/// @param radius The radius of the sphere
	/// @param slices Subdivisions around the z-azis (longitudes).
	/// @param segments Subdivisions along the z-azis (latitudes).
	/// @param sliceStart Counterclockwise angle around the z-axis relative to x-axis.
	/// @param sliceSweep Counterclockwise angle.
	/// @param segmentStart Counterclockwise angle relative to the z-axis.
	/// @param segmentSweep Counterclockwise angle.
	SphereMesh(
		double radius = 1.0,
		int slices = 32,
		int segments = 16,
		double sliceStart = 0.0,
		double sliceSweep = gml::radians(360.0),
		double segmentStart = 0.0,
		double segmentSweep = gml::radians(180.0)
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return axisSwapMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return axisSwapMesh_.vertices(); }

};

}

#endif


