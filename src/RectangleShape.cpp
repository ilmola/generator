// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/RectangleShape.hpp"


using namespace generator;


RectangleShape::RectangleShape(
	const gml::dvec2& size,
	const gml::ivec2& segments
) :
	mergeShape_{
		{{size[0], -size[1]}, size, segments[1]},
		{size, {-size[0], size[1]}, segments[0]},
		{{-size[0], size[1]}, -size, segments[1]},
		{-size, {size[0], -size[1]}, segments[0]}
	}
{ }

