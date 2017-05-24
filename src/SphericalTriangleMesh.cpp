// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/SphericalTriangleMesh.hpp"

#include <stdexcept>


using namespace generator;


SphericalTriangleMesh::Triangles::Triangles(const SphericalTriangleMesh& mesh) :
	mesh_{&mesh},
	row_{0},
	col_{0},
	i_{0}
{ }


bool SphericalTriangleMesh::Triangles::done() const noexcept {
	return row_ == mesh_->segments_;
}

Triangle SphericalTriangleMesh::Triangles::generate() const {
	if (done()) throw std::out_of_range("Done!");

	Triangle triangle;

	if (col_ % 2 == 0) {
		triangle.vertices[0] = i_;
		triangle.vertices[1] = i_ + 1;
		triangle.vertices[2] = i_ + 1 + mesh_->segments_ - row_;
	}
	else {
		triangle.vertices[0] = i_;
		triangle.vertices[1] = i_ + 1 + mesh_->segments_- row_;
		triangle.vertices[2] = i_ + mesh_->segments_ - row_;
	}

	return triangle;
}

void SphericalTriangleMesh::Triangles::next() {
	if (done()) throw std::out_of_range("Done!");

	if (col_ % 2 == 0) ++i_;

	++col_;
	if (col_ == 2 * (mesh_->segments_ - row_) - 1) {
		++i_;
		col_ = 0;
		++row_;
	}
}



SphericalTriangleMesh::Vertices::Vertices(const SphericalTriangleMesh& mesh) :
	mesh_{&mesh},
	row_{0},
	col_{0}
{ }


bool SphericalTriangleMesh::Vertices::done() const noexcept {
	return row_ > mesh_->segments_;
}

MeshVertex SphericalTriangleMesh::Vertices::generate() const {
	if (done()) throw std::out_of_range("Done!");

	MeshVertex vertex;

	if (row_ == mesh_->segments_) {
		vertex.position = mesh_->v2_;
		vertex.texCoord = gml::dvec2{0.5, 1.0};
	}
	else {
		const double t = 1.0 / mesh_->segments_ * row_;
		const double t2 = 1.0 / (mesh_->segments_ - row_) * col_;

		const auto e1 = gml::slerp(mesh_->v0_, mesh_->v2_, t);
		const auto e2 = gml::slerp(mesh_->v1_, mesh_->v2_, t);
		vertex.position = gml::slerp(e1, e2, t2);

		vertex.texCoord[0] = t2;
		vertex.texCoord[1] = t;
	}

	vertex.normal = gml::normalize(vertex.position);
	return vertex;
}

void SphericalTriangleMesh::Vertices::next() {
	if (done()) throw std::out_of_range("Done!");

	++col_;
	if (col_ > mesh_->segments_ - row_) {
		col_ = 0;
		++row_;
	}
}



SphericalTriangleMesh::SphericalTriangleMesh(
	double radius,
	int segments
) :
	SphericalTriangleMesh{
		gml::dvec3{radius, 0.0, 0.0},
		gml::dvec3{0.0, radius, 0.0},
		gml::dvec3{0.0, 0.0, radius},
		segments
	}
{ }


SphericalTriangleMesh::SphericalTriangleMesh(
	const gml::dvec3& v0, const gml::dvec3& v1, const gml::dvec3& v2,
	int segments
) :
	v0_{v0},
	v1_{v1},
	v2_{v2},
	normal_{gml::normal(v0, v1, v2)},
	segments_{segments}
{ }


SphericalTriangleMesh::Triangles SphericalTriangleMesh::triangles() const noexcept {
	return *this;
}

SphericalTriangleMesh::Vertices SphericalTriangleMesh::vertices() const noexcept {
	return *this;
}


