// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_FLIPMESH_HPP
#define GENERATOR_FLIPMESH_HPP

#include "TransformMesh.hpp"
#include "Triangle.hpp"


namespace generator {



/// Flips mesh inside out. Reverses triangles and normals.
template <typename Mesh>
class FlipMesh
{
private:

	using Impl = TransformMesh<Mesh>;
	Impl transformMesh_;

public:

	class Triangles {
	public:

		Triangle generate() const {
			Triangle triangle = triangles_.generate();
			std::swap(triangle.vertices[0], triangle.vertices[2]);
			return triangle;
		}

		bool done() const noexcept { return triangles_.done(); }

		void next() { triangles_.next(); }

	private:

		typename TriangleGeneratorType<TransformMesh<Mesh>>::Type triangles_;

		Triangles(const TransformMesh<Mesh>& mesh) :
			triangles_{mesh.triangles()}
		{ }

	friend class FlipMesh;
	};

	/// @param mesh Source data mesh.
	FlipMesh(Mesh mesh) :
		transformMesh_{std::move(mesh), [] (MeshVertex& vertex) {
			vertex.normal *= -1.0;
		}}
	{ }

	Triangles triangles() const noexcept { return this->transformMesh_; }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformMesh_.vertices(); }


};


template <typename Mesh>
FlipMesh<Mesh> flipMesh(Mesh mesh) {
	return FlipMesh<Mesh>{std::move(mesh)};
}


}



#endif
