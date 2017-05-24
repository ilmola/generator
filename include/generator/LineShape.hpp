// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_LINESHAPE_HPP
#define GENERATOR_LINESHAPE_HPP

#include "ParametricShape.hpp"


namespace generator {


/// A line from a point to a point.
/// @image html LineShape.svg
class LineShape
{
private:

	using Impl = ParametricShape;
	Impl parametricShape_;

public:

	/// @param start Start position
	/// @param end End position
	/// @param segments Number of subdivisions
	LineShape(
		const gml::dvec2& start = {0.0, -1.0},
		const gml::dvec2& end = {0.0, 1.0},
		int segments = 8
	);

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return parametricShape_.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return parametricShape_.vertices(); }

};


}

#endif /* LINE_HPP_ */
