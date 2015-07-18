// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ROUNDEDBOXMESH_HPP
#define GENERATOR_ROUNDEDBOXMESH_HPP

#include "AxisFlipMesh.hpp"
#include "BoxMesh.hpp"
#include "CylinderMesh.hpp"
#include "MergeMesh.hpp"
#include "MirrorMesh.hpp"
#include "TranslateMesh.hpp"
#include "RotateMesh.hpp"
#include "PlaneMesh.hpp"
#include "SphericalTriangleMesh.hpp"


namespace generator {

namespace detail {


class BoxEdge : 
	private TranslateMesh<CylinderMesh> 
{
public:

	BoxEdge(
		const gml::dvec2& position, double radius, double size,
		unsigned slices, unsigned segments
	);

	using TranslateMesh::triangles;

	using TranslateMesh::vertices;

};


class BoxEdges : 
	private MirrorMesh<MirrorMesh<BoxEdge>>
{ 
public:

	BoxEdges(
		const gml::dvec3& size, double radius,
		unsigned slices, unsigned segments
	);

	using MirrorMesh::triangles;

	using MirrorMesh::vertices;

};


class BoxCorner : 
	private TranslateMesh<SphericalTriangleMesh>
{
public:

	BoxCorner(const gml::dvec3& position, double radius, unsigned slices);

	using TranslateMesh::triangles;

	using TranslateMesh::vertices;

};


class BoxCorners :
	private MirrorMesh<MirrorMesh<MirrorMesh<BoxCorner>>>
{
public:
	BoxCorners(const gml::dvec3& size, double radius, unsigned slices);

	using MirrorMesh::triangles;

	using MirrorMesh::vertices;
};



}

/// Rectangular box with rounded edges centered at origin aligned along the x, y
/// and z axis.
/// @image html RoundedBoxMesh.svg
class RoundedBoxMesh : 
	private MergeMesh<
		AxisSwapMesh<detail::BoxFaces>,
		UvFlipMesh<AxisSwapMesh<detail::BoxFaces>>,
		detail::BoxFaces,
		AxisSwapMesh<detail::BoxEdges>,
		AxisSwapMesh<detail::BoxEdges>,
		detail::BoxEdges,
		detail::BoxCorners
	>
{
public:

	/// @param radius Radius of the rounded edges.
	/// @param size Half of the side length in x (0), y (1) and z (2) direction.
	/// @param slices Number subdivions around in the rounded edges.
	/// @param segments Number of subdivisons in x (0), y (1) and z (2)
	/// direction for the flat faces.
	RoundedBoxMesh(
		double radius = 0.25,
		const gml::dvec3& size = {0.75, 0.75, 0.75},
		unsigned slices = 4u,
		const gml::uvec3& segments = {8u, 8u, 8u}
	);

	using MergeMesh::triangles;

	using MergeMesh::vertices;

};


}

#endif
