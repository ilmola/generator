// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef UUID_8FFEADCF19544427BD6E6EC5C071222F
#define UUID_8FFEADCF19544427BD6E6EC5C071222F

#include <algorithm>
#include <limits>

#include "ParametricMesh.hpp"


namespace generator {


/// A bezier patch with D0xD1 control points.
/// @tparam D0 Number of control points along the t[0] axis. Must be > 1.
/// @tparam D1 Number of control points along the t[1] axis. Must be > 1.
/// @image html BezierMesh.svg
template <int D0, int D1>
class BezierMesh
{
private:

	static_assert(D0 > 1, "D0 must be > 1.");
	static_assert(D1 > 1, "D1 must be > 1.");

	using Impl = ParametricMesh;
	Impl mParametricMesh;

	struct ArrayWrapper
	{
		gml::dvec3 data[D1][D0];

		ArrayWrapper(const gml::dvec3 (&p)[D1][D0])
		{
			std::copy(&p[0][0], &p[0][0] + D1 * D0, &data[0][0]);
		}
	};

	explicit BezierMesh(
		const ArrayWrapper& p, const gml::ivec2& segments
	) :
		mParametricMesh{
			[p] (const gml::dvec2& t) {
				MeshVertex vertex;

				vertex.position = gml::bezier2(p.data, t);

				gml::dmat2x3 J = gml::bezier2Jacobian<1>(p.data, t);
				vertex.normal = gml::cross(J[0], J[1]);

				// If the normal was zero try a again near by.
				const double e = std::numeric_limits<double>::epsilon();
				if (dot(vertex.normal, vertex.normal) < e) {
					J = gml::bezier2Jacobian<1>(p.data, t + 10.0 * e);
					vertex.normal = gml::cross(J[0], J[1]);
				}
				vertex.normal = gml::normalize(vertex.normal);

				vertex.texCoord = t;

				return vertex;
			},
			segments
		}
	{ }

public:

	/// @param p Control points
	/// @param segments Number of subdivisions along each axis
	explicit BezierMesh(
		const gml::dvec3 (&p)[D1][D0], const gml::ivec2& segments = {16, 16}
	) :
		// Work around a msvc lambda capture bug by wrapping the array.
		BezierMesh{ArrayWrapper{p}, segments}
	{ }

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return mParametricMesh.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return mParametricMesh.vertices(); }

};


}

#endif
