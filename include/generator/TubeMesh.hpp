// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_TUBEMESH_HPP
#define GENERATOR_TUBEMESH_HPP

#include "CylinderMesh.hpp"
#include "FlipMesh.hpp"
#include "MergeMesh.hpp"
#include "UvFlipMesh.hpp"


namespace generator {


/// Tube (thick cylinder) centered at origin aligned along the z-axis.
/// @image html TubeMesh.svg
class TubeMesh :
	private MergeMesh<CylinderMesh, FlipMesh<UvFlipMesh<CylinderMesh>>>
{
public:

	/// @param radius The outer radius of the cylinder on the xy-plane.
	/// @param innerRadius The inner radius of the cylinder on the xy-plane.
	/// @param size Half of the length of the cylinder along the z-axis.
	/// @param slices Subdivisions around the z-axis.
	/// @param segments Subdivisions along the z-axis.
	/// @param start Counterclockwise angle around the z-axis relative to the x-axis.
	/// @param sweep Counterclockwise angle around the z-axis.
	TubeMesh(
		double radius = 1.0,
		double innerRadius = 0.75,
		double size = 1.0,
		unsigned slices = 32u,
		unsigned segments = 8u,
		double start = 0.0,
		double sweep = gml::radians(360.0)
	);

	using MergeMesh::triangles;

	using MergeMesh::vertices;

};


}

#endif
