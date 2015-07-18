// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/CappedCylinderMesh.hpp"


using namespace generator;
using namespace generator::detail;


Cap::Cap(
	double radius,
	double distance,
	unsigned slices,
	unsigned rings,
	double start,
	double sweep
) :
	TranslateMesh{
		{radius, 0.0, slices, rings, start, sweep},
		{0.0, 0.0, distance}
	}
{ }


CappedCylinderMesh::CappedCylinderMesh(
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
		{radius, size, slices, rings, start, sweep},
		{{{radius, -size, slices, rings, start, sweep}}, true, false}
	}
{ }

