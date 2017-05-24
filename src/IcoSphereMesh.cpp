// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/IcoSphereMesh.hpp"


using namespace generator;


IcoSphereMesh::IcoSphereMesh(double radius, int segments) :
	spherifyMesh_{{1.0, segments}, radius, 1.0}
{ }


