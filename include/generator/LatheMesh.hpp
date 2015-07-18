// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_LATHEMESH_HPP
#define GENERATOR_LATHEMESH_HPP

#include <memory>
#include <vector>

#include "Axis.hpp"
#include "MeshVertex.hpp"
#include "ShapeVertex.hpp"
#include "Triangle.hpp"


namespace generator {



/// Spins a shape around an axis to create a mesh.
/// u-texture coordinate is taken from the shape and v runs from 0 to 1 around
/// the axis counterclockwise.
template <typename Shape>
class LatheMesh {
public:

	class Triangles {
	public:

		Triangles(const Triangles&) = default;
		Triangles(Triangles&&) = default;

		Triangle generate() const {
			Triangle triangle;

			const auto& shapeEdge = shape_Edges.generate();

			unsigned slice = i_ / 2;

			const unsigned delta = mesh_->slices_ + 1 ;

			if (i_ % 2 == 0) {
				triangle.vertices[0] = shapeEdge.vertices[0] * delta + slice;
				triangle.vertices[1] = shapeEdge.vertices[1] * delta + slice;
				triangle.vertices[2] = shapeEdge.vertices[1] * delta + slice + 1;
			}
			else {
				triangle.vertices[0] = shapeEdge.vertices[0] * delta + slice;
				triangle.vertices[1] = shapeEdge.vertices[1] * delta + slice + 1;
				triangle.vertices[2] = shapeEdge.vertices[0] * delta + slice + 1;
			}

			return triangle;
		}

		bool done() const noexcept { return shape_Edges.done(); }

		void next() {
			++i_;
			if (i_ == 2 * mesh_->slices_) {
				i_ = 0;
				shape_Edges.next();
			}
		}

		void reset() noexcept {
			i_ = 0;
			shape_Edges.reset();
		}

	private:

		const LatheMesh* mesh_;

		decltype(mesh_->shape_.edges()) shape_Edges;

		unsigned i_;

		Triangles(const LatheMesh& mesh) :
			mesh_{&mesh},
			shape_Edges{mesh.shape_.edges()},
			i_{0}
		{ }

	friend class LatheMesh;
	};

	class Vertices {
	public:

		Vertices(const Vertices&) = default;
		Vertices(Vertices&&) = default;

		MeshVertex generate() const {
			MeshVertex vertex;

			const auto shapeVertex = shapeVertices_.generate();
			const gml::dvec2 normal = shapeVertex.normal();

			double deltaAngle = mesh_->sweep_ / mesh_->slices_;
			double angle = i_ * deltaAngle + mesh_->start_;

			const gml::dquat q = gml::qrotate(angle, mesh_->axis_);

			vertex.position = gml::transform(q, gml::dvec3{shapeVertex.position});

			vertex.normal = gml::transform(q, gml::dvec3{normal});


			vertex.texCoord[0] = shapeVertex.texCoord;
			vertex.texCoord[1] = angle / mesh_->sweep_;

			return vertex;
		}

		bool done() const noexcept { return shapeVertices_.done(); }

		void next() {
			++i_;

			if (i_ == mesh_->slices_  + 1) {
				i_ = 0;
				shapeVertices_.next();
			}

		}

		void reset() noexcept {
			i_ = 0;
			shapeVertices_.reset();
		}

	private:

		const LatheMesh* mesh_;

		decltype(mesh_->shape_.vertices()) shapeVertices_;

		unsigned i_;

		Vertices(const LatheMesh& mesh) :
			mesh_{&mesh},
			shapeVertices_{mesh.shape_.vertices()},
			i_{0}
		{ }

	friend class LatheMesh;
	};

	/// @param shape The shape to spin.
	/// @param axis Unit length axis to spin around.
	/// @param slices Number of subdivisions around the axis.
	/// @param start Counterclockwise angle around the given axis relative to the xy-plane.
	/// relative to the xy-plane.
	/// @param sweep Counterclockwise angle around the given axis.
	LatheMesh(
		Shape shape,
		const gml::dvec2& axis,
		unsigned slices = 32u,
		double start = 0.0,
		double sweep = gml::radians(360.0)
	) :
		axis_{axis, 0.0},
		shape_{std::move(shape)},
		slices_{slices},
		start_{start},
		sweep_{sweep}
	{ }

	LatheMesh(const LatheMesh&) = default;
	LatheMesh(LatheMesh&&) = default;

	LatheMesh& operator=(const LatheMesh&) = default;
	LatheMesh& operator=(LatheMesh&&) = default;

	Triangles triangles() const noexcept { return *this; }

	Vertices vertices() const noexcept { return *this; }

private:

	gml::dvec3 axis_;

	Shape shape_;

	unsigned slices_;

	double start_;

	double sweep_;

};


template <typename Shape>
LatheMesh<Shape> lathe(
	Shape shape,
	Axis axis = Axis::X,
	unsigned slices = 32,
	double start = 0.0,
	double sweep = gml::radians(360.0)
) {
	return LatheMesh<Shape>{std::move(shape), axis, slices, start, sweep};
}


}


#endif
