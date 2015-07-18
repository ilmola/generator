// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ICOSPHEREMESH_HPP
#define GENERATOR_ICOSPHEREMESH_HPP


#include "IcosahedronMesh.hpp"
#include "SpherifyMesh.hpp"


namespace generator {

/// Icosphere aka subdivided icosahedron
/// @image html IcoSphereMesh.svg
class IcoSphereMesh : 
	private SpherifyMesh<IcosahedronMesh>
{
public:

	/// @param radius Radius of the containing sphere.
	/// @param segments Number of segments per icosahedron edge.
	IcoSphereMesh(double radius = 1.0, unsigned segments = 4u);

	using SpherifyMesh::triangles;

	using SpherifyMesh::vertices;

};


}


#endif
