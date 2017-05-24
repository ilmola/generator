// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_LINEPATH_HPP
#define GENERATOR_LINEPATH_HPP

#include "ParametricPath.hpp"

namespace generator {


/// A path from point to point.
/// @image html LinePath.svg
class LinePath
{
private:

	using Impl = ParametricPath;
	Impl parametricPath_;

public:

	/// @param start Start point of the line.
	/// @param end End point of the line.
	/// @param normal Line normal. Should be parallel to the line.
	/// @param segments Number of subdivisions along the line.
	LinePath(
		const gml::dvec3& start = {0.0, 0.0, -1.0},
		const gml::dvec3& end = {0.0, 0.0, 1.0},
		const gml::dvec3& normal = {1.0, 0.0, 0.0},
		int segments = 8
	);

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return parametricPath_.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return parametricPath_.vertices(); }

};


}


#endif
