// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_TRIANGLE_HPP
#define GENERATOR_TRIANGLE_HPP

#include <gml/gml.hpp>

namespace generator {



class Triangle {
public:

	/// Zero based indices of the triangle vertices in counterclockwise order.
	gml::uvec3 vertices;

	Triangle() :
		vertices{}
	{ }

	Triangle(const gml::uvec3& vertices) :
		vertices{vertices}
	{ }

};

}

#endif
