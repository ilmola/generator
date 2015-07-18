// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_HELIXPATH_HPP
#define GENERATOR_HELIXPATH_HPP

#include "ParametricPath.hpp"

namespace generator {


/// A helix cented at origin aligned along the z-axis.
/// @image html HelixPath.svg
class HelixPath :
	private ParametricPath
{
public:

	/// @param radius Radius from the z-axis
	/// @param size Half of the length along the z-axis.
	/// @param segments Number of subdivisions along the path.
	/// @param start Counterclockwise angle around the z-axis relative to the x-axis.
	/// @param sweep Counterclockwise angle around the z-axis.
	HelixPath(
		double radius = 1.0,
		double size = 1.0,
		unsigned segments = 32u,
		double start = 0.0,
		double sweep = gml::radians(720.0)
	);

	using ParametricPath::edges;

	using ParametricPath::vertices;

};

}

#endif
