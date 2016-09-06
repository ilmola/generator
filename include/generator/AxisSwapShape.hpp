// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_AXISSWAPSHAPE_HPP
#define GENERATOR_AXISSWAPSHAPE_HPP


#include "TransformShape.hpp"

namespace generator {


/// Swaps the x and y axis.
template <typename Shape>
class AxisSwapShape
{
private:

	using Impl = TransformShape<Shape>;
	Impl transformShape_;

public:

	/// @param shape Source data shape.
	AxisSwapShape(Shape shape) :
		transformShape_{
			std::move(shape),
			[] (ShapeVertex& vertex) {
				std::swap(vertex.position[0u], vertex.position[1u]);
				std::swap(vertex.tangent[0u], vertex.tangent[1u]);
			}
		}
	{ }

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return transformShape_.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformShape_.vertices(); }

};


template <typename Shape>
AxisSwapShape<Shape> axisSwapShape(Shape shape) {
	return AxisSwapShape<Shape>{std::move(shape)};
}


}


#endif
