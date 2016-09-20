// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef UUID_781FBB895F744ABCB12D8CDEA0AFA3E4
#define UUID_781FBB895F744ABCB12D8CDEA0AFA3E4

#include <limits>

#include "ParametricShape.hpp"


namespace generator {


/// A bezier curve with D control points.
/// @tparam D Number of control points. 4 = cubic curve. Must be > 1.
/// @image html BezierShape.svg
template <std::size_t D>
class BezierShape
{
private:

	static_assert(D > 1, "D must be > 1.");

	using Impl = ParametricShape;
	Impl mParametricShape;

public:

	/// @param p Control points
	/// @param segments Number of subdivisions
	explicit BezierShape(const gml::dvec2 (&p)[D] = {}, unsigned segments = 16u) :
		mParametricShape{
			// Lambdas will capture arrays by value.
			[p] (double t) {
				ShapeVertex vertex;

				vertex.position = gml::bezier(p, t);

				vertex.tangent = gml::bezierDerivative<1>(p, t);

				// If tangent is zero try again near by.
				const double e = std::numeric_limits<double>::epsilon();
				if (gml::dot(vertex.tangent, vertex.tangent) < e) {
					vertex.tangent = gml::bezierDerivative<1>(p, t + 10.0 * e);
				}

				vertex.tangent = gml::normalize(vertex.tangent);

				vertex.texCoord = t;

				return vertex;
			},
			segments
		}
	{
	}

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return mParametricShape.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return mParametricShape.vertices(); }

};


}

#endif
