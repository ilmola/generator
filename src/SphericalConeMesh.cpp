// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#include "generator/SphericalConeMesh.hpp"


using namespace generator;


namespace {

double calcSize(double radius, double size) {
	return 0.5 * std::sqrt(std::pow(2.0 * size, 2.0) - radius * radius);
}

}



SphericalConeMesh::SphericalConeMesh(
	double radius,
	double size,
	int slices,
	int segments,
	int rings,
	double start,
	double sweep
) :
	translateMesh_{
		{
			{radius, calcSize(radius, size), slices, segments, start, sweep},
			{
				{
					{
						2.0 * size, slices, rings,
						start, sweep, 0.0, std::asin(radius/(2.0*size))
					},
					{0.0, 0.0, -calcSize(radius, size)}
				},
				false, false, true
			}
		},
		{0.0, 0.0, size - calcSize(radius, size)}
	}
{ }

