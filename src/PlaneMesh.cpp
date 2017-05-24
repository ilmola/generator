// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/PlaneMesh.hpp"


using namespace generator;


PlaneMesh::PlaneMesh(
	const gml::dvec2& size,
	const gml::ivec2& segments
) :
	parametricMesh_{
		[size] (const gml::dvec2& t) {
			MeshVertex vertex;
			vertex.position = gml::dvec3{-size + 2.0 * t * size, 0.0};
			vertex.normal = gml::dvec3{0.0, 0.0, 1.0};
			vertex.texCoord = t;
			return vertex;
		},
		segments
	}
{

}
