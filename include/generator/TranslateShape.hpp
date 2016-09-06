// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_TRANSLATESHAPE_HPP
#define GENERATOR_TRANSLATESHAPE_HPP

#include "math.hpp"

#include "TransformShape.hpp"

namespace generator {


/// Translates the position of each vertex by given amount.
template <typename Shape>
class TranslateShape
{
private:

	using Impl = TransformShape<Shape>;
	Impl transformShape_;

public:

	/// @param shape Source data shape.
	/// @param delta Amount to increment vertex positions.
	TranslateShape(Shape shape, const gml::dvec2& delta) :
		transformShape_{
			std::move(shape),
			[delta] (ShapeVertex& value) { value.position += delta;	}
		}
	{ }

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return transformShape_.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformShape_.vertices(); }

};


template <typename Shape>
TranslateShape<Shape> translateShape(Shape shape, const gml::dvec2& delta) {
	return TranslateShape<Shape>{std::move(shape), delta};
}

}

#endif
