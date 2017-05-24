// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef UUID_88C28B4C2B304C399A34364D99D2EC26
#define UUID_88C28B4C2B304C399A34364D99D2EC26

#include <array>
#include <memory>


#include "Triangle.hpp"
#include "MeshVertex.hpp"
#include "BezierMesh.hpp"
#include "utils.hpp"


namespace generator {


/// The Utah Teapot.
/// https://en.wikipedia.org/wiki/Utah_teapot
/// @image html TeapotMesh.svg
class TeapotMesh {
public:

	class Triangles {
	public:

		bool done() const noexcept;
		Triangle generate() const;
		void next();

	private:

		const TeapotMesh* mMesh;

		int mIndex;

		std::shared_ptr<const BezierMesh<4, 4>> mPatchMesh;

		typename TriangleGeneratorType<BezierMesh<4, 4>>::Type mTriangles;

		explicit Triangles(const TeapotMesh& mesh) noexcept;

	friend class TeapotMesh;
	};


	class Vertices {
	public:

		bool done() const noexcept;
		MeshVertex generate() const;
		void next();

	private:

		const TeapotMesh* mMesh;

		int mIndex;

		// Needs be a shared_ptr in order to make copy/move not to mess up the
		// internal pointer in mTriangles.
		std::shared_ptr<const BezierMesh<4, 4>> mPatchMesh;

		typename VertexGeneratorType<BezierMesh<4, 4>>::Type mVertices;

		explicit Vertices(const TeapotMesh& mesh) noexcept;

	friend class TeapotMesh;
	};


	/// Generates the Utah teapot using the original data.
	/// The lid is pointing towards the z axis and the spout towards the x axis.
	/// @param segments The number segments along each patch. Should be >= 1.
	/// If zero empty mesh is generated.
	explicit TeapotMesh(int segments = 8) noexcept;

	Triangles triangles() const noexcept;

	Vertices vertices() const noexcept;

private:

	int mSegments;

	int mPatchVertexCount;

};

}

#endif

