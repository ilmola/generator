// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/RoundedRectangleShape.hpp"


using namespace generator;



RoundedRectangleShape::RoundedRectangleShape(
	double radius,
	const gml::dvec2& size,
	int slices,
	const gml::ivec2& segments
) :
	mergeShape_{
		{{size[0]+radius, -size[1]}, {size[0]+radius, size[1]}, segments[1]},
		{{radius, slices, 0.0, gml::radians(90.0)}, size},
		{{size[0], size[1]+radius}, {-size[0], size[1]+radius}, segments[0]},
		{{radius, slices, gml::radians(90.0), gml::radians(90.0)}, {-size[0], size[1]}},
		{{-size[0]-radius, size[1]}, {-size[0]-radius, -size[1]}, segments[1]},
		{{radius, slices, gml::radians(180.0), gml::radians(90.0)}, -size},
		{{-size[0], -size[1]-radius}, {size[0], -size[1]-radius}, segments[0]},
		{{radius, slices, gml::radians(270.0), gml::radians(90.0)}, {size[0], -size[1]}}
	}
{ }

