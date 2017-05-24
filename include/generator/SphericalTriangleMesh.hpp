// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_SPHERICALTRIANGLEMESH_HPP
#define GENERATOR_SPHERICALTRIANGLEMESH_HPP

#include "math.hpp"

#include "MeshVertex.hpp"
#include "Triangle.hpp"


namespace generator {


/// A triangular region on a surface of a sphere.
/// @image html SphericalTriangleMesh.svg
class SphericalTriangleMesh
{
public:

	class Triangles {
	public:

		bool done() const noexcept;

		Triangle generate() const;

		void next();

	private:

		const SphericalTriangleMesh* mesh_;
		int row_;
		int col_;
		int i_;

		Triangles(const SphericalTriangleMesh& mesh);

	friend class SphericalTriangleMesh;
	};

	class Vertices {
	public:

		bool done() const noexcept;

		MeshVertex generate() const;

		void next();

	private:

		const SphericalTriangleMesh* mesh_;
		int row_;
		int col_;

		Vertices(const SphericalTriangleMesh& mesh);

	friend class SphericalTriangleMesh;
	};

	/// @param radius Radius of the containing sphere.
	/// @param segments Number of subdivisions along each edge.
	SphericalTriangleMesh(
		double radius = 1.0,
		int segments = 4
	);

	/// @param segments Number of subdivisions along each edge.
	SphericalTriangleMesh(
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
