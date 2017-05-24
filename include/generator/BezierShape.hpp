// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef UUID_781FBB895F744ABCB12D8CDEA0AFA3E4
#define UUID_781FBB895F744ABCB12D8CDEA0AFA3E4

#include <algorithm>
#include <limits>

#include "ParametricShape.hpp"


namespace generator {


/// A bezier curve with D control points.
/// @tparam D Number of control points. 4 = cubic curve. Must be > 1.
/// @image html BezierShape.svg
template <int D>
class BezierShape
{
private:

	static_assert(D > 1, "D must be > 1.");

	using Impl = ParametricShape;
	Impl mParametricShape;

	struct ArrayWrapper
	{
		gml::dvec2 data[D];

		ArrayWrapper(const gml::dvec2 (&p)[D])
		{
			std::copy(&p[0], &p[0] + D, &data[0]);
		}
	};


	explicit BezierShape(const ArrayWrapper& p, int segments) :
		mParametricShape{
			[p] (double t) {
				ShapeVertex vertex;

				vertex.position = gml::bezier(p.data, t);

				vertex.tangent = gml::bezierDerivative<1>(p.data, t);

				// If tangent is zero try again near by.
				const double e = std::numeric_limits<double>::epsilon();
				if (gml::dot(vertex.tangent, vertex.tangent) < e) {
					vertex.tangent = gml::bezierDerivative<1>(p.data, t + 10.0 * e);
				}

				vertex.tangent = gml::normalize(vertex.tangent);

				vertex.texCoord = t;

				return vertex;
			},
			segments
		}
	{
	}

public:

	/// @param p Control points
	/// @param segments Number of subdivisions
	explicit BezierShape(const gml::dvec2 (&p)[D], int segments = 16) :
		// Work around a msvc lambda capture bug by wrapping the array.
		BezierShape{ArrayWrapper{p}, segments}
	{ }

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return mParametricShape.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return mParametricShape.vertices(); }

};


}

#endif
