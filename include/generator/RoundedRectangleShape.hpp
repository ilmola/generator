// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ROUNDEDRECTANGLESHAPE_HPP
#define GENERATOR_ROUNDEDRECTANGLESHAPE_HPP

#include "CircleShape.hpp"
#include "LineShape.hpp"
#include "MergeShape.hpp"
#include "TranslateShape.hpp"


namespace generator {



/// Rectangle with rounded corners centered at origin aligned along the x and y axis.
class RoundedRectangleShape
{
private:

	using Impl = MergeShape<
		LineShape, TranslateShape<CircleShape>,
		LineShape, TranslateShape<CircleShape>,
		LineShape, TranslateShape<CircleShape>,
		LineShape, TranslateShape<CircleShape>
	>;
	Impl mergeShape_;

public:

	/// @param radius Radius of the rounded corners.
	/// @param size Half of a length of an edge.
	/// @param slices Number of subdivisions in each rounded corner.
	/// @param segments Number of subdivisions along each edge.
	RoundedRectangleShape(
		double radius = 0.25,
		const gml::dvec2& size = {0.75, 0.75},
		int slices = 4,
		const gml::ivec2& segments = {8, 8}
	);

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return mergeShape_.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return mergeShape_.vertices(); }

};


}

#endif
