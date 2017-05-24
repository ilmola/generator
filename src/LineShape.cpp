// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/LineShape.hpp"


using namespace generator;


LineShape::LineShape(
	const gml::dvec2& start,
	const gml::dvec2& end,
	int segments
) :
	parametricShape_{
		[start, end] (double t) {
			ShapeVertex vertex;

			vertex.position = start + t * (end - start);
			vertex.tangent = normalize(end - start);
			vertex.texCoord = t;

			return vertex;
		},
		segments
	}
{

}
