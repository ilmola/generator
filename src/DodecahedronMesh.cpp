// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/DodecahedronMesh.hpp"
#include "generator/Iterator.hpp"

#include <array>
#include <memory>

using namespace generator;


static const double a = (1.0 + std::sqrt(5.0)) / 2.0;

static const std::array<gml::dvec3, 20> vertices {{
	{ 1.0,  1.0, -1.0},
	{-1.0,  1.0, -1.0},
	{ 1.0, -1.0, -1.0},
	{-1.0, -1.0, -1.0},
	{ 1.0,  1.0,  1.0},
	{-1.0,  1.0,  1.0},
	{ 1.0, -1.0,  1.0},
	{-1.0, -1.0,  1.0},

	{0.0,  1.0/a, -a},
	{0.0, -1.0/a, -a},
	{0.0,  1.0/a,  a},
	{0.0, -1.0/a,  a},

	{ 1.0/a,  a, 0.0},
	{-1.0/a,  a, 0.0},
	{ 1.0/a, -a, 0.0},
	{-1.0/a, -a, 0.0},

	{ a, 0.0, -1.0/a},
	{-a, 0.0, -1.0/a},
	{ a, 0.0,  1.0/a},
	{-a, 0.0,  1.0/a}
}};


static const std::array<std::array<int, 5>, 12> polygons{{
	{{ 0u, 12u,  4u, 18u, 16u}}, // 0
	{{18u,  6u, 14u,  2u, 16u}}, // 1
	{{ 4u, 10u, 11u,  6u, 18u}}, // 2
	{{11u,  7u, 15u, 14u,  6u}}, // 3
	{{ 7u, 11u, 10u,  5u, 19u}}, // 4
	{{17u,  3u, 15u,  7u, 19u}}, // 5
	{{ 9u,  2u, 14u, 15u,  3u}}, // 6
	{{ 1u,  8u,  9u,  3u, 17u}}, // 7
	{{10u,  4u, 12u, 13u,  5u}}, // 8
	{{ 5u, 13u,  1u, 17u, 19u}}, // 9
	{{ 0u,  8u,  1u, 13u, 12u}}, // 10
	{{ 0u, 16u,  2u,  9u,  8u}}  // 11
}};


static std::vector<gml::dvec3> makeVertices(int faceIndex) noexcept {
	std::vector<gml::dvec3> result(5);
	for (int i = 0; i < 5; ++i) {
		result.at(i) = gml::normalize(vertices.at(polygons.at(faceIndex)[i]));
	}
	return result;
}


DodecahedronMesh::Triangles::Triangles(const DodecahedronMesh& mesh) noexcept :
	mMesh{&mesh},
	mFaceIndex{0},
	mFaceMesh{std::make_shared<ConvexPolygonMesh>(makeVertices(0), mMesh->mSegments, mMesh->mRings)},
	mTriangles{mFaceMesh->triangles()}
{ }



bool DodecahedronMesh::Triangles::done() const noexcept {
	return mFaceIndex == ::polygons.size();
}


Triangle DodecahedronMesh::Triangles::generate() const {
	if (done()) throw std::out_of_range("Done!");

	Triangle triangle = mTriangles.generate();

	const int base = mFaceIndex * mMesh->mFaceVertexCount;

	triangle.vertices[0] += base;
	triangle.vertices[1] += base;
	triangle.vertices[2] += base;

	return triangle;
}


void DodecahedronMesh::Triangles::next() {
	if (done()) throw std::out_of_range("Done!");

	mTriangles.next();

	if (mTriangles.done()) {
		++mFaceIndex;

		if (!done()) {
			mFaceMesh = std::make_shared<ConvexPolygonMesh>(
				makeVertices(mFaceIndex),
				mMesh->mSegments
			);

			mTriangles = mFaceMesh->triangles();
		}
	}
}



DodecahedronMesh::Vertices::Vertices(const DodecahedronMesh& mesh) noexcept :
	mMesh{&mesh},
	mFaceIndex{0},
	mFaceMesh{std::make_shared<ConvexPolygonMesh>(
		makeVertices(0),
		mMesh->mSegments,
		mMesh->mRings
	)},
	mVertices{mFaceMesh->vertices()}
{

}


bool DodecahedronMesh::Vertices::done() const noexcept {
	return mFaceIndex == ::polygons.size();
}


MeshVertex DodecahedronMesh::Vertices::generate() const {

	MeshVertex vertex = mVertices.generate();

	vertex.position *= mMesh->mRadius;

	return vertex;
}


void DodecahedronMesh::Vertices::next() {
	mVertices.next();

	if (mVertices.done()) {
		++mFaceIndex;

		if (!done()) {
			mFaceMesh = std::make_shared<ConvexPolygonMesh>(
				makeVertices(mFaceIndex),
				mMesh->mSegments,
				mMesh->mRings
			);

			mVertices = mFaceMesh->vertices();
		}
	}
}



DodecahedronMesh::DodecahedronMesh(double radius, int segments, int rings) noexcept :
	mRadius{radius},
	mSegments{segments},
	mRings{rings},
	mFaceVertexCount{count(ConvexPolygonMesh{1.0, 5u, segments, rings}.vertices())}
{

}


DodecahedronMesh::Triangles DodecahedronMesh::triangles() const noexcept {
	return Triangles{*this};
}


DodecahedronMesh::Vertices DodecahedronMesh::vertices() const noexcept {
	return Vertices{*this};
}



