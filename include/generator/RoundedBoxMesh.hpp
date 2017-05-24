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


class BoxEdge
{
private:

	using Impl = TranslateMesh<CylinderMesh>;
	Impl translateMesh_;

public:

	BoxEdge(
		const gml::dvec2& position, double radius, double size,
		int slices, int segments
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return translateMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return translateMesh_.vertices(); }

};


class BoxEdges
{
private:

	using Impl = MirrorMesh<MirrorMesh<BoxEdge>>;
	Impl mirrorMesh_;

public:

	BoxEdges(
		const gml::dvec3& size, double radius,
		int slices, int segments
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return mirrorMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return mirrorMesh_.vertices(); }

};


class BoxCorner
{
private:

	using Impl = TranslateMesh<SphericalTriangleMesh>;
	Impl translateMesh_;

public:

	BoxCorner(const gml::dvec3& position, double radius, int slices);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return translateMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return translateMesh_.vertices(); }

};


class BoxCorners
{
private:

	using Impl = MirrorMesh<MirrorMesh<MirrorMesh<BoxCorner>>>;
	Impl mirrorMesh_;

public:
	BoxCorners(const gml::dvec3& size, double radius, int slices);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return mirrorMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return mirrorMesh_.vertices(); }
};



}

/// Rectangular box with rounded edges centered at origin aligned along the x, y
/// and z axis.
/// @image html RoundedBoxMesh.svg
class RoundedBoxMesh
{
private:

	using Impl = MergeMesh<
		AxisSwapMesh<detail::BoxFaces>,
		UvFlipMesh<AxisSwapMesh<detail::BoxFaces>>,
		detail::BoxFaces,
		AxisSwapMesh<detail::BoxEdges>,
		AxisSwapMesh<detail::BoxEdges>,
		detail::BoxEdges,
		detail::BoxCorners
	>;
	Impl mergeMesh_;

public:

	/// @param radius Radius of the rounded edges.
	/// @param size Half of the side length in x (0), y (1) and z (2) direction.
	/// @param slices Number subdivions around in the rounded edges.
	/// @param segments Number of subdivisons in x (0), y (1) and z (2)
	/// direction for the flat faces.
	RoundedBoxMesh(
		double radius = 0.25,
		const gml::dvec3& size = {0.75, 0.75, 0.75},
		int slices = 4,
		const gml::ivec3& segments = {8, 8, 8}
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return mergeMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return mergeMesh_.vertices(); }

};


}

#endif
