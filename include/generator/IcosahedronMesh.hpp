// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ICOSAHEDRONMESH_HPP
#define GENERATOR_ICOSAHEDRONMESH_HPP

#include <array>

#include "Triangle.hpp"
#include "MeshVertex.hpp"
#include "TriangleMesh.hpp"
#include "utils.hpp"


namespace generator {


/// Regular icosahedron centered at origin with given radius.
/// @image html IcosahedronMesh.svg
class IcosahedronMesh {
private:

	class Triangles {
	public:

		bool done() const noexcept;
		Triangle generate() const;
		void next();
		void reset() noexcept;

	private:

		const IcosahedronMesh* mesh_;

		unsigned i_;

		TriangleMesh triangle_;

		typename TriangleGeneratorType<TriangleMesh>::Type triangles_;

		Triangles(const IcosahedronMesh& mesh);

	friend class IcosahedronMesh;
	};


	class Vertices {
	public:

		bool done() const noexcept;
		MeshVertex generate() const;
		void next();
		void reset() noexcept;

	private:

		const IcosahedronMesh* mesh_;

		unsigned i_;

		TriangleMesh triangle_;

		typename VertexGeneratorType<TriangleMesh>::Type vertices_;

		Vertices(const IcosahedronMesh& mesh);

	friend class IcosahedronMesh;
	};

	double radius_;

	unsigned segments_;

	unsigned faceVertexCount_;

public:

	/// @param radius The radius of the enclosing sphere
	/// @param segments Number subdivisions per edge.
	IcosahedronMesh(double radius = 1.0, unsigned segments = 1);

	Triangles triangles() const noexcept;

	Vertices vertices() const noexcept;

};

}

#endif

