// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/CapsuleMesh.hpp"


using namespace generator;


CapsuleMesh::CapsuleMesh(
	double radius,
	double size,
	int slices,
	int segments,
	int rings,
	double start,
	double sweep
) :
	mergeMesh_{
		{radius, size, slices, segments, start, sweep},
		{
			{radius, slices, rings, start, sweep, 0.0, gml::radians(90.0)},
			{0.0, 0.0, size}
		},
		{
			{
				radius, slices, rings, start, sweep,
				gml::radians(90.0), gml::radians(90.0)
			},
			{0.0, 0.0, -size}
		}
	}
{

}


