// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_SUBDIVIDEMESH_HPP
#define GENERATOR_SUBDIVIDEMESH_HPP

#include <vector>
#include <map>

#include "Edge.hpp"
#include "MeshVertex.hpp"
#include "Triangle.hpp"
#include "utils.hpp"


namespace generator {


template <typename Mesh, unsigned Iterations>
class SubdivideMesh :
	private SubdivideMesh<SubdivideMesh<Mesh, Iterations-1>, 1> {
public:

	SubdivideMesh(Mesh mesh) :
		SubdivideMesh<SubdivideMesh<Mesh, Iterations-1>, 1>{
			SubdivideMesh<Mesh, Iterations-1>{std::move(mesh)}
		}
	{ }

	using SubdivideMesh<SubdivideMesh<Mesh, Iterations-1>, 1>::triangles;

	using SubdivideMesh<SubdivideMesh<Mesh, Iterations-1>, 1>::vertices;

};


template <typename Mesh>
class SubdivideMesh<Mesh, 0> :
	private Mesh
{
public:

	SubdivideMesh(Mesh mesh) :
		Mesh{std::move(mesh)}
	{ }

	using Mesh::triangles;

	using Mesh::vertices;
};



/// Subdivides each triangle to 4 parts by splitting edges.
template <typename Mesh>
class SubdivideMesh<Mesh, 1> {
public:

	class Triangles {
	public:

		bool done() const noexcept { return triangles_.done(); }
	
		Triangle generate() const {
			if (i_ == 0) triangle_ = triangles_.generate();

			if (i_ == 3) {
				return Triangle{{
					vertexFromEdge(triangle_.vertices[0], triangle_.vertices[1]),
					vertexFromEdge(triangle_.vertices[1], triangle_.vertices[2]),
					vertexFromEdge(triangle_.vertices[2], triangle_.vertices[0])
				}};
			}
			
			unsigned j = (i_ + 1) % 3;
			unsigned k = (i_ + 2) % 3;
			return Triangle{{
				triangle_.vertices[i_],
				vertexFromEdge(triangle_.vertices[i_], triangle_.vertices[j]),
				vertexFromEdge(triangle_.vertices[k], triangle_.vertices[i_])
			}};
		}

		void next() {
			++i_;
			if (i_ == 4) {
				i_ = 0;
				triangles_.next();
			}
		}

		void reset() noexcept { i_ = 0; triangles_.reset(); }

	private:

		const SubdivideMesh* mesh_;

		unsigned i_;

		typename TriangleGeneratorType<Mesh>::Type triangles_;

		mutable Triangle triangle_;

		Triangles(const SubdivideMesh& mesh) :
			mesh_{&mesh},
			i_{0},
			triangles_{mesh.mesh_.triangles()},
			triangle_{}
		{ }

		unsigned vertexFromEdge(unsigned a, unsigned b) const {
			if (a > b) std::swap(a, b);
			return static_cast<unsigned>(mesh_->vertexCache_.size()) + mesh_->edgeMap_.at({a, b});
		}

	friend class SubdivideMesh;
	};


	class Vertices {
	public:

		bool done() const noexcept { 
			return 
				vertexIndex_ == mesh_->vertexCache_.size() &&
				edgeIndex_ == mesh_->edgeCache_.size();
		}

		MeshVertex generate() const {
			if (vertexIndex_ < mesh_->vertexCache_.size())
				return mesh_->vertexCache_[vertexIndex_];

			const MeshVertex& v1 = mesh_->vertexCache_[mesh_->edgeCache_[edgeIndex_].vertices[0]];
			const MeshVertex& v2 = mesh_->vertexCache_[mesh_->edgeCache_[edgeIndex_].vertices[1]];

			MeshVertex vertex;
			vertex.position = gml::mix(v1.position, v2.position, 0.5);
			vertex.texCoord = gml::mix(v1.texCoord, v2.texCoord, 0.5);
			vertex.normal = gml::normalize(gml::mix(v1.normal, v2.normal, 0.5));
			return vertex;
		}

		void next() {
			if (vertexIndex_ < mesh_->vertexCache_.size()) ++vertexIndex_;
			else ++edgeIndex_;
		}

		void reset() noexcept { vertexIndex_ = 0; edgeIndex_ = 0; }

	private:

		const SubdivideMesh* mesh_;

		unsigned edgeIndex_;
		unsigned vertexIndex_;

		Vertices(const SubdivideMesh& mesh) :
			mesh_{&mesh},
			edgeIndex_{0},
			vertexIndex_{0}
		{ }

	friend class SubdivideMesh;
	};


	SubdivideMesh(Mesh mesh) :
		mesh_{std::move(mesh)}
	{
		for (const MeshVertex& vertex : mesh_.vertices()) {
			vertexCache_.push_back(vertex);
		}

		for (const Triangle& triangle : mesh_.triangles()) {
			for (unsigned i = 0; i < 3; ++i) {
				unsigned j = (i + 1) % 3;

				Edge e{{triangle.vertices[i], triangle.vertices[j]}};
				if (e.vertices[0] > e.vertices[1])
					std::swap(e.vertices[0], e.vertices[1]);

				if (edgeMap_.find(e.vertices) == edgeMap_.end()) {
					edgeMap_[e.vertices] = static_cast<unsigned>(edgeCache_.size());
					edgeCache_.push_back(e);
				}

			}
		}
	}


	Triangles triangles() const noexcept { return *this; }

	Vertices vertices() const noexcept { return *this; }

private:

	Mesh mesh_;

	std::vector<Edge> edgeCache_;

	std::map<gml::uvec2, unsigned> edgeMap_;

	std::vector<MeshVertex> vertexCache_;

};


}

#endif

