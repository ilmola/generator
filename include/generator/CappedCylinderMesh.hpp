// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_CAPPEDCYLINDERMESH_HPP
#define GENERATOR_CAPPEDCYLINDERMESH_HPP

#include "FlipMesh.hpp"
#include "LatheMesh.hpp"
#include "LineShape.hpp"
#include "MergeMesh.hpp"
#include "CylinderMesh.hpp"
#include "TranslateMesh.hpp"
#include "DiskMesh.hpp"
#include "RotateMesh.hpp"
#include "UvFlipMesh.hpp"


namespace generator {

namespace detail {

class Cap
{
private:

	using Impl = TranslateMesh<DiskMesh>;
	Impl translateMesh_;

public:

	Cap(
		double radius,
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



/// Like CylinderMesh but with end caps.
/// @image html CappedCylinderMesh.svg
class CappedCylinderMesh
{
private:

	using Impl = MergeMesh<
		CylinderMesh,
		detail::Cap,
		UvFlipMesh<FlipMesh<detail::Cap>>
	>;
	Impl mergeMesh_;

public:

	/// @param radius Radius of the cylinder along the xy-plane.
	/// @param size Half of the length cylinder along the z-axis.
	/// @param slices Number of subdivisions around the z-axis.
	/// @param segments Number of subdivisions along the z-axis.
	/// @param rings Number of subdivisions on the caps.
	/// @param start Counterclockwise angle around the z-axis relative to x-axis.
	/// @param sweep Counterclockwise angle around the z-axis.
	CappedCylinderMesh(
		double radius = 1.0,
		double size = 1.0,
		int slices = 32,
		int segments = 8,
		int rings = 4,
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
