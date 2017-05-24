// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/SpringMesh.hpp"

using namespace generator;


SpringMesh::SpringMesh(
	double minor,
	double major,
	double size,
	int slices,
	int segments,
	double minorStart,
	double minorSweep,
	double majorStart,
	double majorSweep
) :
	extrudeMesh_{
		{minor, slices, minorStart, minorSweep},
		{major, size, segments, majorStart, majorSweep}
	}
{ }


