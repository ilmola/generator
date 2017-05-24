// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_TRIANGLEMESH_HPP
#define GENERATOR_TRIANGLEMESH_HPP

#include "math.hpp"


#include "MeshVertex.hpp"
#include "Triangle.hpp"


namespace generator {


/// A triangular mesh on the xy -plane.
/// @image html TriangleMesh.svg
class TriangleMesh
{
public:

	class Triangles {
	public:

		bool done() const noexcept;
		Triangle generate() const;
		void next();

	private:

		const TriangleMesh* mesh_;
		int row_;
		int col_;
		int i_;

		Triangles(const TriangleMesh& mesh);

	friend class TriangleMesh;
	};

	class Vertices {
	public:

		bool done() const noexcept;
		MeshVertex generate() const;
		void next();

	private:

		const TriangleMesh* mesh_;
		int row_;
		int col_;

		Vertices(const TriangleMesh& mesh);

	friend class TriangleMesh;
	};

	/// Makes a regular triangle centered at origin.
	/// @param radius The radius of the containing circle.
	/// @param segments The number of segments along each edge. Must be >= 1.
	explicit TriangleMesh(double radius = 1.0, int segments = 4);

	/// @param v0,v1,v2 The vertex positions of the triangle.
	/// @param segments The number of segments along each edge. Must be >= 1.
	TriangleMesh(
		const gml::dvec3& v0, const gml::dvec3& v1, const gml::dvec3& v2,
		int segments = 4
	);

	Triangles triangles() const noexcept;

	Vertices vertices() const noexcept;

private:

	gml::dvec3 v0_, v1_, v2_;

	gml::dvec3 normal_;

	int segments_;

};


}


#endif
