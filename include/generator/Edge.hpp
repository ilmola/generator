// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_EDGE_HPP
#define GENERATOR_EDGE_HPP

#include <gml/gml.hpp>

namespace generator {

class Edge {
public:

	gml::uvec2 vertices;

	Edge() :
		vertices{}
	{ }

	Edge(const gml::uvec2& vertices) :
		vertices{vertices}
	{ }

	Edge(const Edge&) = default;
	Edge(Edge&&) = default;

	Edge& operator=(const Edge&) = default;
	Edge& operator=(Edge&&) = default;
};

}

#endif
