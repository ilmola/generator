// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/TubeMesh.hpp"


using namespace generator;


TubeMesh::TubeMesh(
	double radius,
	double innerRadius,
	double size,
	int slices,
	int segments,
	double start,
	double sweep
) :
	mergeMesh_{
		{radius, size, slices, segments, start, sweep},
		{{{innerRadius, size, slices, segments, start, sweep}, true, false}}
	}
{ }

