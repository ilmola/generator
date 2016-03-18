// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_EMPTYMESH_HPP
#define GENERATOR_EMPTYMESH_HPP

#include "Iterator.hpp"
#include "MeshVertex.hpp"
#include "Triangle.hpp"


namespace generator {


/// Empty Mesh with zero vertices and triangles.
class EmptyMesh {
public:

	class Triangles {
	public:
		Triangle generate() const;
		bool done() const noexcept;
		void next();
	private:

		Triangles();

	friend class EmptyMesh;
	};

	class Vertices {
	public:

		MeshVertex generate() const;
		bool done() const noexcept;
		void next();

	private:

		Vertices();

	friend class EmptyMesh;
	};

	EmptyMesh();

	Triangles triangles() const noexcept;

	Vertices vertices() const noexcept;

};


}

#endif
