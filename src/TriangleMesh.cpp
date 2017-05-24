// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/TriangleMesh.hpp"

#include <stdexcept>

using namespace generator;



TriangleMesh::Triangles::Triangles(const TriangleMesh& mesh) :
	mesh_{&mesh},
	row_{0},
	col_{0},
	i_{0}
{ }

bool TriangleMesh::Triangles::done() const noexcept {
	return row_ == mesh_->segments_;
}

Triangle TriangleMesh::Triangles::generate() const {
	if (done()) throw std::out_of_range("Done!");

	Triangle triangle;

	if (col_ % 2 == 0) {
		triangle.vertices[0] = i_;
		triangle.vertices[1] = i_ + 1;
		triangle.vertices[2] = i_ + 1 + mesh_->segments_- row_;
	}
	else {
		triangle.vertices[0] = i_;
		triangle.vertices[1] = i_ + 1 + mesh_->segments_- row_;
		triangle.vertices[2] = i_ + mesh_->segments_- row_;
	}

	return triangle;
}

void TriangleMesh::Triangles::next() {
	if (done()) throw std::out_of_range("Done!");

	if (col_ % 2 == 0) ++i_;

	++col_;
	if (col_ == 2 * (mesh_->segments_ - row_) - 1) {
		++i_;
		col_ = 0;
		++row_;
	}
}




TriangleMesh::Vertices::Vertices(const TriangleMesh& mesh) :
	mesh_{&mesh},
	row_{0},
	col_{0}
{ }

bool TriangleMesh::Vertices::done() const noexcept {
	return row_ > mesh_->segments_;
}

MeshVertex TriangleMesh::Vertices::generate() const {
	if (done()) throw std::out_of_range("Done!");

	MeshVertex vertex;

	if (row_ == mesh_->segments_) {
		vertex.position = mesh_->v2_;
		vertex.texCoord = gml::dvec2{0.5, 1.0};
	}
	else {
		const double t = 1.0 / mesh_->segments_ * row_;
		const double t2 = 1.0 / (mesh_->segments_ - row_) * col_;

		const auto e1 = gml::mix(mesh_->v0_, mesh_->v2_, t);
		const auto e2 = gml::mix(mesh_->v1_, mesh_->v2_, t);

		vertex.position = gml::mix(e1, e2, t2);

		vertex.texCoord[0] = t2;
		vertex.texCoord[1] = t;
	}

	vertex.normal = mesh_->normal_;
	return vertex;
}

void TriangleMesh::Vertices::next() {
	if (done()) throw std::out_of_range("Done!");

	++col_;
	if (col_ > mesh_->segments_ - row_) {
		col_ = 0;
		++row_;
	}
}




TriangleMesh::TriangleMesh(double radius, int segments) :
	TriangleMesh{
		radius * gml::normalize(gml::dvec3{-1.0, -1.0, 0.0}),
		radius * gml::normalize(gml::dvec3{1.0, -1.0, 0.0}),
		gml::dvec3{0.0, radius, 0.0},
		segments
	}
{ }



TriangleMesh::TriangleMesh(
	const gml::dvec3& v0, const gml::dvec3& v1, const gml::dvec3& v2,
	int segments
) :
	v0_{v0},
	v1_{v1},
	v2_{v2},
	normal_{gml::normal(v0, v1, v2)},
	segments_{segments}
{ }

TriangleMesh::Triangles TriangleMesh::triangles() const noexcept {
	return {*this};
}

TriangleMesh::Vertices TriangleMesh::vertices() const noexcept {
	return {*this};
}

