// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/TorusKnotMesh.hpp"


using namespace generator;


TorusKnotMesh::TorusKnotMesh(
	int p,
	int q,
	int slices,
	int segments
) :
	extrudeMesh_{
		{0.25, slices, 0.0, gml::radians(360.0)},
		{p, q, segments}
	}
{ }

