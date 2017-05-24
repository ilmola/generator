// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#include "generator/SphereMesh.hpp"

using namespace generator;


SphereMesh::SphereMesh(
	double radius,
	int slices,
	int segments,
	double sliceStart,
	double sliceSweep,
	double segmentStart,
	double segmentSweep
) :
	axisSwapMesh_{
		{
			{radius, segments, segmentStart, segmentSweep},
			{1.0, 0.0}, slices, sliceStart, sliceSweep
		},
		Axis::Y, Axis::Z, Axis::X
	}
{ }


