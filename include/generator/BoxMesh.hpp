// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_BOXMESH_HPP
#define GENERATOR_BOXMESH_HPP

#include "AxisSwapMesh.hpp"
#include "FlipMesh.hpp"
#include "PlaneMesh.hpp"
#include "MergeMesh.hpp"
#include "TranslateMesh.hpp"
#include "PlaneMesh.hpp"
#include "UvFlipMesh.hpp"
#include "UvSwapMesh.hpp"

namespace generator {

namespace detail {


class BoxFace : private TranslateMesh<PlaneMesh> {
public:

	BoxFace(const gml::dvec2& size, const gml::uvec2& segments, double delta);

	using TranslateMesh::triangles;

	using TranslateMesh::vertices;

};


class BoxFaces : private MergeMesh<BoxFace, UvFlipMesh<FlipMesh<BoxFace>>> {
public:

	BoxFaces(const gml::dvec2& size, const gml::uvec2& segments, double delta);

	using MergeMesh::triangles;

	using MergeMesh::vertices;

};


}



/// Rectangular box centered at origin aligned along the x, y and z axis.
/// @image html BoxMesh.svg
class BoxMesh :
	private MergeMesh<
		AxisSwapMesh<detail::BoxFaces>,
		UvFlipMesh<AxisSwapMesh<detail::BoxFaces>>,
		detail::BoxFaces
	>
{
public:

	/// @param size Half of the side length in x (0), y (1) and z (2) direction.
	/// @param segments Number of subdivisions in x (0), y (1) and z (2) direction.
	BoxMesh(
		const gml::dvec3& size = {1.0, 1.0, 1.0},
		const gml::uvec3& segments = {8u, 8u, 8u}
	);

	using MergeMesh::triangles;

	using MergeMesh::vertices;

};


}

#endif
