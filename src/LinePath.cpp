// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#include "generator/LinePath.hpp"


using namespace generator;


LinePath::LinePath(
	const gml::dvec3& start,
	const gml::dvec3& end,
	const gml::dvec3& normal,
	int segments
):
	parametricPath_{
		[start, end, normal] (double t) {
			PathVertex vertex;

			vertex.position = start + t * (end - start);
			vertex.tangent = normalize(end - start);
			vertex.normal = normal;
			vertex.texCoord = t;

			return vertex;
		},
		segments
	}
{ }

