// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/IcosahedronMesh.hpp"
#include "generator/Iterator.hpp"

#include <array>

using namespace generator;


static const double a = (1.0 + std::sqrt(5.0)) / 2.0;
static const double d = std::sqrt(1.0 + a * a);
static const double x = 1.0 / d;
static const double y = a / d;

static const std::array<gml::dvec3, 12> vertices {{
	{-x, y, 0.0},
	{x, y, 0.0},
	{-x, -y, 0.0},
	{x, -y, 0.0},
	{0.0, -x, y},
	{0.0, x, y},
	{0.0, -x, -y},
	{0.0, x, -y},
	{y, 0.0, -x},
	{y, 0.0, x},
	{-y, 0.0, -x},
	{-y, 0.0, x}
}};


static const std::array<gml::ivec3, 20> triangles{{
	{0,  11, 5},
	{0,  5,  1},
	{0,  1,  7},
	{0,  7,  10},
	{0,  10, 11},
	{1,  5,  9},
	{5,  11, 4},
	{11, 10, 2},
	{10, 7,  6},
	{7,  1,  8},
	{3,  9,  4},
	{3,  4,  2},
	{3,  2,  6},
	{3,  6,  8},
	{3,  8,  9},
	{4,  9,  5},
	{2,  4,  11},
	{6,  2,  10},
	{8,  6,  7},
	{9,  8,  1}
}};


IcosahedronMesh::Triangles::Triangles(const IcosahedronMesh& mesh) :
	mesh_{&mesh},
	i_{0},
	triangleMesh_{std::make_shared<TriangleMesh>(
		::vertices[::triangles[0][0]],
		::vertices[::triangles[0][1]],
		::vertices[::triangles[0][2]],
		mesh.segments_
	)},
	triangles_{triangleMesh_->triangles()}
{ }



bool IcosahedronMesh::Triangles::done() const noexcept {
	return i_ == static_cast<int>(::triangles.size());
}


Triangle IcosahedronMesh::Triangles::generate() const {
	if (done()) throw std::out_of_range("Done!");

	Triangle triangle = triangles_.generate();

	const int base = i_ * mesh_->faceVertexCount_;

	triangle.vertices[0] +=  base;
	triangle.vertices[1] +=  base;
	triangle.vertices[2] +=  base;

	return triangle;
}


void IcosahedronMesh::Triangles::next() {
	if (done()) throw std::out_of_range("Done!");

	triangles_.next();

	if (triangles_.done()) {
		++i_;

		if (!done()) {
			triangleMesh_ = std::make_shared<TriangleMesh>(
				::vertices[::triangles[i_][0]],
				::vertices[::triangles[i_][1]],
				::vertices[::triangles[i_][2]],
				mesh_->segments_
			);

			triangles_ =  triangleMesh_->triangles();
		}
	}
}




IcosahedronMesh::Vertices::Vertices(const IcosahedronMesh& mesh) :
	mesh_{&mesh},
	i_{0},
	triangleMesh_{std::make_shared<TriangleMesh>(
		::vertices[::triangles[0][0]],
		::vertices[::triangles[0][1]],
		::vertices[::triangles[0][2]],
		mesh_->segments_
	)},
	vertices_{triangleMesh_->vertices()}
{

}


bool IcosahedronMesh::Vertices::done() const noexcept {
	return i_ == static_cast<int>(::triangles.size());
}

MeshVertex IcosahedronMesh::Vertices::generate() const {
	if (done()) throw std::out_of_range("Done!");

	MeshVertex vertex = vertices_.generate();

	vertex.position *= mesh_->radius_;

	return vertex;
}

void IcosahedronMesh::Vertices::next() {
	if (done()) throw std::out_of_range("Done!");

	vertices_.next();

	if (vertices_.done()) {
		++i_;

		if (!done()) {
			triangleMesh_ = std::make_shared<TriangleMesh>(
				::vertices[::triangles[i_][0]],
				::vertices[::triangles[i_][1]],
				::vertices[::triangles[i_][2]],
				mesh_->segments_
			);

			vertices_ = triangleMesh_->vertices();
		}
	}
}




IcosahedronMesh::IcosahedronMesh(double radius, int segments) :
	radius_{radius},
	segments_{segments},
	faceVertexCount_{count(TriangleMesh{1.0, segments}.vertices())}
{ }

IcosahedronMesh::Triangles IcosahedronMesh::triangles() const noexcept {
	return {*this};
}

IcosahedronMesh::Vertices IcosahedronMesh::vertices() const noexcept {
	return {*this};
}



