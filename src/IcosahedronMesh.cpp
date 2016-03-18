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


static const std::array<gml::uvec3, 20> triangles{{
	{0u, 11u, 5u},
	{0u, 5u, 1u},
	{0u, 1u, 7u},
	{0u, 7u, 10u},
	{0u, 10u, 11u},
	{1u, 5u, 9u},
	{5u, 11u, 4u},
	{11u, 10u, 2u},
	{10u, 7u, 6u},
	{7u, 1u, 8u},
	{3u, 9u, 4u},
	{3u, 4u, 2u},
	{3u, 2u, 6u},
	{3u, 6u, 8u},
	{3u, 8u, 9u},
	{4u, 9u, 5u},
	{2u, 4u, 11u},
	{6u, 2u, 10u},
	{8u, 6u, 7u},
	{9u, 8u, 1u}
}};


IcosahedronMesh::Triangles::Triangles(const IcosahedronMesh& mesh) :
	mesh_{&mesh},
	i_{0},
	triangle_{
		::vertices[::triangles[0][0]],
		::vertices[::triangles[0][1]],
		::vertices[::triangles[0][2]],
		mesh.segments_
	},
	triangles_{triangle_.triangles()}
{ }



bool IcosahedronMesh::Triangles::done() const noexcept {
	return i_ == ::triangles.size();
}


Triangle IcosahedronMesh::Triangles::generate() const {
	if (done()) throw std::out_of_range("Done!");

	Triangle triangle = triangles_.generate();

	const unsigned base = i_ * mesh_->faceVertexCount_;

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
			triangle_ = TriangleMesh{
				::vertices[::triangles[i_][0]],
				::vertices[::triangles[i_][1]],
				::vertices[::triangles[i_][2]],
				mesh_->segments_
			};

			triangles_ =  triangle_.triangles();
		}
	}
}




IcosahedronMesh::Vertices::Vertices(const IcosahedronMesh& mesh) :
	mesh_{&mesh},
	i_{0},
	triangle_{
		::vertices[::triangles[0][0]],
		::vertices[::triangles[0][1]],
		::vertices[::triangles[0][2]],
		mesh_->segments_
	},
	vertices_{triangle_.vertices()}
{

}


bool IcosahedronMesh::Vertices::done() const noexcept {
	return i_ == ::triangles.size();
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
			triangle_ = TriangleMesh{
				::vertices[::triangles[i_][0]],
				::vertices[::triangles[i_][1]],
				::vertices[::triangles[i_][2]],
				mesh_->segments_
			};

			vertices_ = triangle_.vertices();
		}
	}
}




IcosahedronMesh::IcosahedronMesh(double radius, unsigned segments) :
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



