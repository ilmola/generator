// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_EDGE_HPP
#define GENERATOR_EDGE_HPP

#include "math.hpp"

namespace generator {

class Edge {
public:

	gml::ivec2 vertices;

	Edge() noexcept :
		vertices{}
	{ }

	explicit Edge(const gml::ivec2& vertices) noexcept :
		vertices{vertices}
	{ }

};

}

#endif
