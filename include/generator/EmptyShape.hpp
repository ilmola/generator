// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_EMPTYSHAPE_HPP
#define GENERATOR_EMPTYSHAPE_HPP

#include "ShapeVertex.hpp"
#include "Edge.hpp"


namespace generator {


/// Empty shape with zero vertices and edges.
class EmptyShape {
public:

	class Edges {
	public:
		Edge generate() const;
		bool done() const noexcept;
		void next();
	private:
		Edges();
	friend class EmptyShape;
	};

	class Vertices {
	public:
		ShapeVertex generate() const;
		bool done() const noexcept;
		void next();
	private:
		Vertices();
	friend class EmptyShape;
	};

	Edges edges() const noexcept;

	Vertices vertices() const noexcept;

};


}

#endif
