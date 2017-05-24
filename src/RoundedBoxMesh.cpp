// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/RoundedBoxMesh.hpp"


using namespace generator;
using namespace generator::detail;




BoxEdge::BoxEdge(
	const gml::dvec2& position, double radius, double size,
	int slices, int segments
) :
	translateMesh_{
		{radius, size, slices, segments, 0.0, gml::radians(90.0)},
		gml::dvec3{position, 0.0}
	}
{ }


BoxEdges::BoxEdges(
	const gml::dvec3& size, double radius,
	int slices, int segments
) :
	mirrorMesh_{
		{
			{gml::dvec2{size}, radius, size[2], slices, segments},
			Axis::Y
		},
		Axis::X
	}
{ }


BoxCorner::BoxCorner(
	const gml::dvec3& position, double radius, int slices
) :
	translateMesh_{
		{
			gml::dvec3{radius, 0.0, 0.0},
			gml::dvec3{0.0, radius, 0.0},
			gml::dvec3{0.0, 0.0, radius},
			slices
		},
		position
	}
{ }


BoxCorners::BoxCorners(const gml::dvec3& size, double radius, int slices) :
	mirrorMesh_{{{{size, radius, slices}, Axis::X}, Axis::Y}, Axis::Z}
{ }



RoundedBoxMesh::RoundedBoxMesh(
	double radius,
	const gml::dvec3& size,
	int slices,
	const gml::ivec3& segments
) :
	mergeMesh_{
		{
			{{size[1], size[2]}, {segments[1], segments[2]}, size[0] + radius},
			Axis::Z, Axis::X, Axis::Y
		},
		{
			{
				{{size[0], size[2]}, {segments[0], segments[2]}, size[1] + radius},
				Axis::X, Axis::Z, Axis::Y
			},
			true, false
		},
		{{size[0], size[1]}, {segments[0], segments[1]}, size[2] + radius},
		{
			{{size[2], size[1], size[0]}, radius, slices, segments[0]},
			Axis::Z, Axis::Y, Axis::X
		},
		{
			{{size[0], size[2], size[1]}, radius, slices, segments[1]},
			Axis::X, Axis::Z, Axis::Y
		},
		{size, radius, slices, segments[2]},
		{size, radius, slices}
	}
{ }

