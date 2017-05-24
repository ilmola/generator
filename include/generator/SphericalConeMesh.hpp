// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_SPHERICALCONEMESH_HPP
#define GENERATOR_SPHERICALCONEMESH_HPP


#include "AxisFlipMesh.hpp"
#include "ConeMesh.hpp"
#include "MergeMesh.hpp"
#include "SphereMesh.hpp"
#include "TranslateMesh.hpp"


namespace generator {


/// A cone with a spherical cap centered at origin tip pointing towards z-axis.
/// Each point on the cap has equal distance from the tip.
/// @image html SphericalConeMesh.svg
class SphericalConeMesh
{
private:

	using Impl = TranslateMesh<MergeMesh<ConeMesh, AxisFlipMesh<TranslateMesh<SphereMesh>>>>;
	Impl translateMesh_;

public:

	/// @param radius Radius of the negative z end on the xy-plane.
	/// @param size Half of the distance between cap and tip along the z-axis.
	/// @param slices Number of subdivisions around the z-axis.
	/// @param segments Number subdivisions along the z-axis.
	/// @param rings Number subdivisions in the cap.
	/// @param start Counterclockwise angle around the z-axis relative to the positive x-axis.
	/// @param sweep Counterclockwise angle around the z-axis.
	SphericalConeMesh(
		double radius = 1.0,
		double size = 1.0,
		int slices = 32,
		int segments = 8,
		int rings = 4,
		double start = 0.0,
		double sweep = gml::radians(360.0)
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return translateMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return translateMesh_.vertices(); }

};


}

#endif
