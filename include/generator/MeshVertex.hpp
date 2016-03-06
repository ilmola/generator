// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_MESHVERTEX_HPP
#define GENERATOR_MESHVERTEX_HPP

#include "math.hpp"

namespace generator {


class MeshVertex {
public:

	gml::dvec3 position;

	/// Unit vector perpendicular to the surface.
	gml::dvec3 normal;

	/// UV texture coordinates
	gml::dvec2 texCoord;

	MeshVertex() noexcept :
		position{},
		normal{},
		texCoord{}
	{ }

};



}

#endif
