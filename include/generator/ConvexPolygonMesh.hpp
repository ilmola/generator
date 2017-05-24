// Copyright 2016 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef UUID_418D292D0BAB4AB4832E1CFEB92F0589
#define UUID_418D292D0BAB4AB4832E1CFEB92F0589

#include <vector>

#include "math.hpp"

#include "MeshVertex.hpp"
#include "Triangle.hpp"


namespace generator {



/// A polygonal disk with arbitrary number of corners.
/// Subdivided along each side to segments and radially to rings.
/// @image html ConvexPolygonMesh.svg
class ConvexPolygonMesh {
private:

	class Triangles {
	public:
		bool done() const noexcept;
		Triangle generate() const;
		void next();

	private:

		const ConvexPolygonMesh* mMesh;

		bool mOdd;

		int mSegmentIndex;

		int mSideIndex;

		int mRingIndex;

		explicit Triangles(const ConvexPolygonMesh&) noexcept;

	friend class ConvexPolygonMesh;
	};

	class Vertices {
	public:

		bool done() const noexcept;
		MeshVertex generate() const;
		void next();

	private:

		const ConvexPolygonMesh* mMesh;

		bool mCenterDone;

		int mSegmentIndex;

		int mSideIndex;

		int mRingIndex;

		explicit Vertices(const ConvexPolygonMesh&) noexcept;

	friend class ConvexPolygonMesh;
	};

	std::vector<gml::dvec3> mVertices;

	int mSegments;

	int mRings;

	gml::dvec3 mCenter;

	gml::dvec3 mNormal;

	gml::dvec3 mTangent;

	gml::dvec3 mBitangent;

	gml::dvec2 mTexDelta;

public:

	/// @param radius The radius the enclosing circle.
	/// @param sides The number of sides. Should be >= 3. If <3 an empty mesh
	/// is generated.
	/// @param segments The number of segments per side. Should be >= 1. If zero
	/// an empty mesh is generated.
	/// @param rings The number of radial segments. Should be >= 1. = yelds an empty mesh.
	explicit ConvexPolygonMesh(
		double radius = 1.0, int sides = 5, int segments = 4, int rings = 4
	) noexcept;

	//// @param vertices The corner vertex coordinates. Should form a convex polygon.
	explicit ConvexPolygonMesh(
		const std::vector<gml::dvec2>& vertices, int segments = 1, int rings = 1
	) noexcept;

	/// @param vertices The corner vertex coordinates. Should be coplanar and
	/// form a convex polygon.
	/// calculated as an avarage.
	explicit ConvexPolygonMesh(
		std::vector<gml::dvec3> vertices, int segments = 1, int rings = 1
	) noexcept;

	Triangles triangles() const noexcept;

	Vertices vertices() const noexcept;

};

}

#endif
