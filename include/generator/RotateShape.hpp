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
class RotateShape
{
private:

	using Impl = TransformShape<Shape>;
	Impl transformShape_;

public:

	/// @param shape Source data shape.
	/// @param angle Counterclockwise angle.
	RotateShape(Shape shape, double angle) :
		transformShape_{
			std::move(shape),
			[angle] (ShapeVertex& value) {
				auto rotation = gml::rotate(angle);
				value.position = gml::transform(rotation, value.position);
				value.tangent = gml::transform(rotation, value.tangent);
			}
		}
	{ }

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return transformShape_.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformShape_.vertices(); }

};


template <typename Shape>
RotateShape<Shape> rotateShape(Shape shape, double angle) {
	return RotateShape<Shape>{std::move(shape), angle};
}

}


#endif
