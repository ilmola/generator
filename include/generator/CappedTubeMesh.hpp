// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_CAPPEDTUBEMESH_HPP
#define GENERATOR_CAPPEDTUBEMESH_HPP

#include "FlipMesh.hpp"
#include "MergeMesh.hpp"
#include "TubeMesh.hpp"
#include "TranslateMesh.hpp"
#include "DiskMesh.hpp"


namespace generator {

namespace detail {

class TubeCap
{
private:

	using Impl = TranslateMesh<DiskMesh>;
	Impl translateMesh_;

public:

	TubeCap(
		double radius,
		double innerRadius,
		double distance,
		int slices,
		int rings,
		double start,
		double sweep
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return translateMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return translateMesh_.vertices(); }

};

}



/// Like TubeMesh but with end caps.
/// @image html CappedTubeMesh.svg
class CappedTubeMesh
{
private:

	using Impl = MergeMesh<TubeMesh, detail::TubeCap, FlipMesh<detail::TubeCap>>;
	Impl mergeMesh_;

public:

	/// @param radius The outer radius of the cylinder on the xy-plane.
	/// @param innerRadius The inner radius of the cylinder on the xy-plane.
	/// @param size Half of the length of the cylinder along the z-axis.
	/// @param slices Number nubdivisions around the z-axis.
	/// @param segments Number of subdivisions along the z-axis.
	/// @param rings Number radial subdivisions in the cap.
	/// @param start Counterclockwise angle around the z-axis relative to the x-axis.
	/// @param sweep Counterclockwise angle around the z-axis.
	CappedTubeMesh(
		double radius = 1.0,
		double innerRadius = 0.75,
		double size = 1.0,
		int slices = 32,
		int segments = 8,
		int rings = 1,
		double start = 0.0,
		double sweep = gml::radians(360.0)
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return mergeMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return mergeMesh_.vertices(); }

};


}

#endif
