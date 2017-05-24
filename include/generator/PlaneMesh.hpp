// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_PLANE_HPP
#define GENERATOR_PLANE_HPP

#include "ParametricMesh.hpp"

namespace generator {



/// A plane (rectangular grid) on the xy -plane normal pointing towards z-axis.
/// @image html PlaneMesh.svg
class PlaneMesh
{
private:

	using Impl = ParametricMesh;
	Impl parametricMesh_;

public:

	/// @param size Half of the side length in x (0) and y (1) direction.
	/// @param segments Number of subdivisions in the x (0) and y (1) direction.
	PlaneMesh(
		const gml::dvec2& size = {1.0, 1.0},
		const gml::ivec2& segments = {8, 8}
	);

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return parametricMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return parametricMesh_.vertices(); }

};


}

#endif
