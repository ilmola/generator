// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/CappedConeMesh.hpp"


using namespace generator;


CappedConeMesh::CappedConeMesh(
	double radius,
	double size,
	unsigned slices,
	unsigned segments,
	unsigned rings,
	double start,
	double sweep
) :
	MergeMesh{
		{radius, size, slices, segments, start, sweep},
		{{{
			DiskMesh{radius, 0.0, slices, rings},
			gml::dvec3{0.0, 0.0, -size}
		}}, true, false}
	}
{ }



