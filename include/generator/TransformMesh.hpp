// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_TRANSLATOR_HPP
#define GENERATOR_TRANSLATOR_HPP

#include <functional>

#include "MeshVertex.hpp"
#include "utils.hpp"


namespace generator {


/// Apply a mutator function to each vertex.
template <typename Mesh>
class TransformMesh : private Mesh
{
public:

	class Vertices {
	public:

		MeshVertex generate() const {
			auto vertex = vertices_.generate();
			mesh_->mutate_(vertex);
			return vertex;
		}

		bool done() const noexcept { return vertices_.done(); }

		void next() { vertices_.next(); }

	private:

		const TransformMesh* mesh_;

		typename VertexGeneratorType<Mesh>::Type vertices_;

		Vertices(const TransformMesh& mesh) :
			mesh_{&mesh},
			vertices_{static_cast<const Mesh&>(mesh).vertices()}
		{ }

	friend class TransformMesh;
	};

	/// @param mesh Source data mesh.
	/// @param mutate Callback function that gets called once per vertex.
	TransformMesh(Mesh mesh, std::function<void (MeshVertex&)> mutate) :
		Mesh{std::move(mesh)},
		mutate_{mutate}
	{ }

	using Mesh::triangles;

	Vertices vertices() const noexcept { return *this; }

private:

	std::function<void(MeshVertex&)> mutate_;

};


template <typename Mesh>
TransformMesh<Mesh> transformMesh(
	Mesh mesh, std::function<void(MeshVertex&)> mutate
) {
	return TransformMesh<Mesh>{std::move(mesh), std::move(mutate)};
}

}

#endif
