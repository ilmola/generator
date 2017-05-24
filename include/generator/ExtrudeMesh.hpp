// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_EXTRUDEMESH_HPP
#define GENERATOR_EXTRUDEMESH_HPP

#include "MeshVertex.hpp"
#include "PathVertex.hpp"
#include "ShapeVertex.hpp"
#include "Triangle.hpp"
#include "Edge.hpp"
#include "Iterator.hpp"


namespace generator {



/// Extrude a shape along a path.
/// The shape normal becomes the mesh normal.
/// u-texture coordinate is taken from the shape and v from the path.
template <typename Shape, typename Path>
class ExtrudeMesh {
public:

	class Triangles {
	public:

		Triangle generate() const {
			Triangle triangle;

			const auto& shapeEdge = shapeEdges_.generate();
			const auto& pathEdge = pathEdges_.generate();

			if (odd_ == 0) {
				triangle.vertices[0] =
					shapeEdge.vertices[0] + pathEdge.vertices[0] * mesh_->shapeVertexCount_;
				triangle.vertices[1] =
					shapeEdge.vertices[1] + pathEdge.vertices[1] * mesh_->shapeVertexCount_;
				triangle.vertices[2] =
					shapeEdge.vertices[0] + pathEdge.vertices[1] * mesh_->shapeVertexCount_;
			}
			else {
				triangle.vertices[0] =
					shapeEdge.vertices[0] + pathEdge.vertices[0] * mesh_->shapeVertexCount_;
				triangle.vertices[1] =
					shapeEdge.vertices[1] + pathEdge.vertices[0] * mesh_->shapeVertexCount_;
				triangle.vertices[2] =
					shapeEdge.vertices[1] + pathEdge.vertices[1] * mesh_->shapeVertexCount_;
			}

			return triangle;
		}

		bool done() const noexcept { return pathEdges_.done(); }

		void next() {
			odd_ = !odd_;

			if (odd_) {
				shapeEdges_.next();
				if (shapeEdges_.done()) {
					pathEdges_.next();
					shapeEdges_ = mesh_->shape_.edges();
				}
			}
		}

	private:

		const ExtrudeMesh* mesh_;

		decltype(mesh_->shape_.edges()) shapeEdges_;

		decltype(mesh_->path_.edges()) pathEdges_;

		bool odd_;

		Triangles(const ExtrudeMesh& mesh) :
			mesh_{&mesh},
			shapeEdges_{mesh.shape_.edges()},
			pathEdges_{mesh.path_.edges()},
			odd_{true}
		{
		}

	friend class ExtrudeMesh;
	};

	class Vertices {
	public:

		MeshVertex generate() const {
			MeshVertex vertex;

			const auto& shapeVertex = shapeVertices_.generate();
			const auto& pathVertex = pathVertices_.generate();

			gml::dvec3 pathBinormal = pathVertex.binormal();
			vertex.position =
				pathVertex.position +
				shapeVertex.position[0] * pathVertex.normal +
				shapeVertex.position[1] * pathBinormal;

			gml::dvec2 shapeNormal = shapeVertex.normal();
			vertex.normal =
				shapeNormal[0] * pathVertex.normal +
				shapeNormal[1] * pathBinormal;

			vertex.texCoord[0] = shapeVertex.texCoord;
			vertex.texCoord[1] = pathVertex.texCoord;

			return vertex;
		}

		bool done() const noexcept { return pathVertices_.done(); }

		void next() {
			shapeVertices_.next();
			if (shapeVertices_.done()) {
				pathVertices_.next();
				shapeVertices_ = mesh_->shape_.vertices();
			}
		}

	private:

		const ExtrudeMesh* mesh_;

		decltype(mesh_->shape_.vertices()) shapeVertices_;

		decltype(mesh_->path_.vertices()) pathVertices_;

		Vertices(const ExtrudeMesh& mesh) :
			mesh_{&mesh},
			shapeVertices_{mesh.shape_.vertices()},
			pathVertices_{mesh.path_.vertices()}
		{ }

	friend class ExtrudeMesh;
	};

	Triangles triangles() const noexcept { return *this; }

	Vertices vertices() const noexcept { return *this; }

	/// @param shape Shape to be extruded.
	/// @param path Path to extrude along.
	ExtrudeMesh(Shape shape, Path path) :
		shape_{std::move(shape)},
		path_{std::move(path)},
		shapeVertexCount_{count(shape_.vertices())}
	{ }

private:

	Shape shape_;

	Path path_;

	int shapeVertexCount_;

};



template <typename Shape, typename Path>
ExtrudeMesh<Shape, Path> extrudeMesh(Shape shape, Path path) {
	return ExtrudeMesh<Shape, Path>{std::move(shape), std::move(path)};
}


}

#endif
