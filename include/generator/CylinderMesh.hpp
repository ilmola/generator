// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_CYLINDERMESH_HPP
#define GENERATOR_CYLINDERMESH_HPP

#include "AxisSwapMesh.hpp"
#include "LatheMesh.hpp"
#include "LineShape.hpp"
#include "UvFlipMesh.hpp"

namespace generator {



/// Cylinder centered at origin aligned along the z-axis.
/// @image html CylinderMesh.svg
class CylinderMesh :
	private AxisSwapMesh<LatheMesh<LineShape>>
{
public:

	/// @param radius Radius of the cylinder along the xy-plane.
	/// @param size Half of the length of the cylinder along the z-axis.
	/// @param slices Subdivisions around the z-axis.
	/// @param segments Subdivisions along the z-axis.
	/// @param start Counterclockwise angle around the z-axis relative to the x-axis.
	/// @param sweep Counterclockwise angle around the z-axis.
	CylinderMesh(
		double radius = 1.0,
		double size = 1.0,
		unsigned slices = 32u,
		unsigned segments = 8u,
		double start = 0.0,
		double sweep = gml::radians(360.0)
	); 

	using AxisSwapMesh::triangles;

	using AxisSwapMesh::vertices;

};


}

#endif
