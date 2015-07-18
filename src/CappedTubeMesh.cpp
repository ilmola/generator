// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/CappedTubeMesh.hpp"

using namespace generator;

using namespace generator::detail;


TubeCap::TubeCap(
	double radius,
	double innerRadius,
	double distance,
	unsigned slices,
	unsigned rings,
	double start,
	double sweep
) :
	TranslateMesh{
		{radius, innerRadius, slices, rings, start, sweep},
		{0.0, 0.0, distance}
	}
{ }


CappedTubeMesh::CappedTubeMesh(
	double radius,
	double innerRadius,
	double size,
	unsigned slices,
	unsigned segments,
	unsigned rings,
	double start,
	double sweep
) :
	MergeMesh{
		{radius, innerRadius, size, slices, segments, start, sweep},
		{radius, innerRadius, size, slices, rings, start, sweep},
		{{radius, innerRadius, -size, slices, rings, start, sweep}},
	}
{ }

