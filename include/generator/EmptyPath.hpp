// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_EMPTYPATH_HPP
#define GENERATOR_EMPTYPATH_HPP

#include "Iterator.hpp"
#include "PathVertex.hpp"
#include "Edge.hpp"

namespace generator {


/// Empty path with zero vertices and edges.
class EmptyPath {
public:

	class Edges {
	public:

		Edge generate() const;
		bool done() const noexcept;
		void next();

	private:

		Edges();

	friend class EmptyPath;
	};

	class Vertices {
	public:

		PathVertex generate() const;
		bool done() const noexcept;
		void next();

	private:

		Vertices();

	friend class EmptyPath;
	};

	EmptyPath();

	Edges edges() const noexcept;

	Vertices vertices() const noexcept;

};


}

#endif
