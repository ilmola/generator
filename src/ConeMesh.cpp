// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/ConeMesh.hpp"


using namespace generator;


ConeMesh::ConeMesh(
	double radius,
	double size,
	int slices,
	int segments,
	double start,
	double sweep
) :
	axisSwapMesh_{
		{
			{{size, 0.0}, {-size, radius}, segments},
			{1.0, 0.0}, slices, start, sweep
		},
		Axis::Y, Axis::Z, Axis::X
	}
{ }
