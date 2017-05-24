// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#include "generator/DiskMesh.hpp"


using namespace generator;


DiskMesh::DiskMesh(
	double radius,
	double innerRadius,
	int slices,
	int rings,
	double start,
	double sweep
) :
	axisSwapMesh_{
		{
			{{0.0, innerRadius}, {0.0, radius}, rings},
			{1.0, 0.0}, slices, start, sweep
		},
		Axis::Y, Axis::Z, Axis::X
	}
{ }
