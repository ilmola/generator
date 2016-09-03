// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_AXISFLIPMESH_HPP
#define GENERATOR_AXISFLIPMESH_HPP

#include "TransformMesh.hpp"
#include "Triangle.hpp"

namespace generator {


/// Flips (mirrors) the mesh along one or more axis.
/// Texture coordinates are not flipped.
/// Also reverses triangle vertex order if needed.
template <typename Mesh>
class AxisFlipMesh
{
private:

	using Impl = TransformMesh<Mesh>;
	Impl transformMesh_;

public:

	class Triangles {
	public:

		Triangle generate() const {
			Triangle triangle = triangles_.generate();
			if (mesh_->flip_)
				std::swap(triangle.vertices[0], triangle.vertices[2]);
			return triangle;
		}

		bool done() const noexcept { return triangles_.done(); }

		void next() { triangles_.next(); }

	private:

		const AxisFlipMesh* mesh_;

		typename TriangleGeneratorType<TransformMesh<Mesh>>::Type triangles_;

		Triangles(const AxisFlipMesh& mesh) :
			mesh_{&mesh},
			triangles_{mesh.transformMesh_.triangles()}
		{ }

	friend class AxisFlipMesh;
	};

	///@param mesh Source data mesh.
	///@param x Flip x
	///@param y Flip y
	///@param z Flip z
	AxisFlipMesh(Mesh mesh, bool x, bool y, bool z) :
		transformMesh_{
			std::move(mesh),
			[x, y, z] (MeshVertex& vertex) {
				if (x) {
					vertex.position[0] *= -1.0;
					vertex.normal[0] *= -1.0;
				}

				if (y) {
					vertex.position[1] *= -1.0;
					vertex.normal[1] *= -1.0;
				}

				if (z) {
					vertex.position[2] *= -1.0;
					vertex.normal[2] *= -1.0;
				}
			}
		},
		flip_{false}
	{
		if (x) flip_ = !flip_;
		if (y) flip_ = !flip_;
		if (z) flip_ = !flip_;
	}

	Triangles triangles() const noexcept { return {*this}; }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformMesh_.vertices(); }

private:

	bool flip_;

};


template <typename Mesh>
AxisFlipMesh<Mesh> axisFlipMesh(Mesh mesh, bool x, bool y, bool z) {
	return AxisFlipMesh<Mesh>{std::move(mesh), x, y, z};
}



}



#endif
