// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_FLIPSHAPE_HPP
#define GENERATOR_FLIPSHAPE_HPP


#include "Edge.hpp"
#include "TransformShape.hpp"


namespace generator {


/// Flips shape direction. Reverses edges and tangents.
template <typename Shape>
class FlipShape
{
private:

	using Impl = TransformShape<Shape>;
	Impl transformShape_;

public:

	class Edges {
	public:

		Edge generate() const {
			Edge edge = edges_.generate();
			std::swap(edge.vertices[0], edge.vertices[1]);
			return edge;
		}

		bool done() const noexcept { return edges_.done(); }

		void next() { edges_.next(); }

	private:

		typename EdgeGeneratorType<TransformShape<Shape>>::Type edges_;

		Edges(const TransformShape<Shape>& shape) :
			edges_{shape.edges()}
		{ }

	friend class FlipShape;
	};

	/// @param shape Source data shape.
	FlipShape(Shape shape) :
		transformShape_{
			std::move(shape),
			[] (ShapeVertex& vertex) {
				vertex.tangent *= -1.0;
			}
		}
	{ }

	Edges edges() const noexcept { return {*this}; }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformShape_.vertices(); }


};


template <typename Shape>
FlipShape<Shape> flipShape(Shape shape) {
	return FlipShape<Shape>{std::move(shape)};
}


}



#endif
