// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/HelixPath.hpp"


using namespace generator;


HelixPath::HelixPath(
	double radius,
	double size,
	int segments,
	double start,
	double sweep
) :
	parametricPath_{
		[radius, size, start, sweep] (double t) {
			PathVertex vertex;
			const double angle = start + t * sweep;
			const double sine = std::sin(angle);
			const double cosine = std::cos(angle);

			vertex.position = gml::dvec3{
				radius * cosine,
				radius * sine,
				2.0 * t * size - size
			};

			vertex.tangent = gml::normalize(gml::dvec3{
				-radius * sine,
				radius * cosine,
				2.0 * size / sweep,
			});

			vertex.normal = gml::dvec3{cosine, sine, 0.0};

			vertex.texCoord = t;

			return vertex;
		},
		segments
	}
{ }


