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


class BoxFace
{
private:

	using Impl = TranslateMesh<PlaneMesh>;
	Impl translateMesh_;

public:

	BoxFace(const gml::dvec2& size, const gml::ivec2& segments, double delta);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return translateMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return translateMesh_.vertices(); }

};


class BoxFaces
{
private:

	using Impl = MergeMesh<BoxFace, UvFlipMesh<FlipMesh<BoxFace>>>;
	Impl mergeMesh_;

public:

	BoxFaces(const gml::dvec2& size, const gml::ivec2& segments, double delta);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return mergeMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return mergeMesh_.vertices(); }

};


}



/// Rectangular box centered at origin aligned along the x, y and z axis.
/// @image html BoxMesh.svg
class BoxMesh
{
private:

	using Impl = MergeMesh<
		AxisSwapMesh<detail::BoxFaces>,
		UvFlipMesh<AxisSwapMesh<detail::BoxFaces>>,
		detail::BoxFaces
	>;
	Impl mergeMesh_;

public:

	/// @param size Half of the side length in x (0), y (1) and z (2) direction.
	/// @param segments The number of segments in x (0), y (1) and z (2)
	/// directions. All should be >= 1. If any one is zero faces in that
	/// direction are not genereted. If more than one is zero the mesh is empty.
	explicit BoxMesh(
		const gml::dvec3& size = {1.0, 1.0, 1.0},
		const gml::ivec3& segments = {8, 8, 8}
	) noexcept;

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return mergeMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return mergeMesh_.vertices(); }

};


}

#endif
