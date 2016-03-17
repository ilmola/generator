// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_SHAPEGENERATOR_HPP
#define GENERATOR_SHAPEGENERATOR_HPP

#include "math.hpp"


namespace generator {


/// A point on a path.
/// Position and assosiated coordinate system.
class ShapeVertex {
public:

	gml::dvec2 position;

	/// Unit length vector parallel to the shape at this point.
	/// Also the y-axis of the shape's local coordinate system.
	gml::dvec2 tangent;

	double texCoord;

	ShapeVertex() :
		position{},
		tangent{},
		texCoord{}
	{ }

	/// Returns the tangent rotated 90 dec clockwise.
	/// Also the x-axis of the shape's local coordinate system.
	gml::dvec2 normal() const noexcept {
		return -gml::cross(tangent);
	}

};


}

#endif
