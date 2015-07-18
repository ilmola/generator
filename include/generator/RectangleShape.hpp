// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_RECTANGLESHAPE_HPP
#define GENERATOR_RECTANGLESHAPE_HPP


#include "LineShape.hpp"
#include "MergeShape.hpp"


namespace generator {



/// Rectangle centered at origin aligned along the x and y axis.
/// @image html RectangleShape.svg
class RectangleShape : 
	private MergeShape<LineShape, LineShape, LineShape, LineShape> 
{
public:

	/// @param size Half of the length of an edge.
	/// @param segments Number of subdivisions per edge.
	RectangleShape(
		const gml::dvec2& size = gml::dvec2{1.0, 1.0},
		const gml::uvec2& segments = gml::uvec2{8u, 8u}
	);

	using MergeShape::edges;

	using MergeShape::vertices;

};


}

#endif
