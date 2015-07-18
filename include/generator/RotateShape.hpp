// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ROTATESHAPE_HPP
#define GENERATOR_ROTATESHAPE_HPP

#include "TransformShape.hpp"


namespace generator {


/// Rotates a shape around the origin on the xy-plane.
template <typename Shape>
class RotateShape : private TransformShape<Shape>
{
public:

	/// @param shape Source data shape.
	/// @param angle Counterclockwise angle.
	RotateShape(Shape shape, double angle) :
		TransformShape<Shape>{
			std::move(shape),
			[angle] (ShapeVertex& value) {
				auto rotation = gml::rotate(angle);
				value.position = gml::transform(rotation, value.position);
				value.tangent = gml::transform(rotation, value.tangent);
			}
		}
	{ }

	using TransformShape<Shape>::edges;

	using TransformShape<Shape>::vertices;

};


template <typename Shape>
RotateShape<Shape> rotateShape(Shape shape, double angle) {
	return RotateShape<Shape>{std::move(shape), angle};
}

}


#endif
