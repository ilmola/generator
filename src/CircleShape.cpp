// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#include "generator/CircleShape.hpp"


using namespace generator;


CircleShape::CircleShape(
	double radius,
	int segments,
	double start,
	double sweep
) :
	parametricShape_{
		[radius, start, sweep] (double t) {
			const double angle = t * sweep + start;
			const double sine = std::sin(angle);
			const double cosine = std::cos(angle);

			ShapeVertex vertex;
			vertex.position = gml::dvec2{radius * cosine, radius * sine};
			vertex.tangent = gml::dvec2{-sine, cosine};
			vertex.texCoord = t;

			return vertex;
		},
		segments
	}
{ }
