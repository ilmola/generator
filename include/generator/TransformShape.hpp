// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_SHAPETRANSLATOR_HPP
#define GENERATOR_SHAPETRANSLATOR_HPP

#include "ShapeVertex.hpp"
#include "utils.hpp"

namespace generator {



/// Apply a mutator function to each vertex.
template <typename Shape>
class TransformShape
{
private:

	using Impl = Shape;
	Impl shape_;

public:

	class Vertices {
	public:

		ShapeVertex generate() const {
			auto temp = vertices_.generate();
			shape_->mutate_(temp);
			return temp;
		}

		bool done() const noexcept { return vertices_.done(); }

		void next() { vertices_.next(); }

	private:

		const TransformShape* shape_;

		typename VertexGeneratorType<Shape>::Type  vertices_;

		Vertices(const TransformShape& shape) :
			shape_{&shape},
			vertices_{shape.shape_.vertices()}
		{ }

	friend class TransformShape;
	};

	/// @param shape Source data shape.
	/// @param mutate Callback function that gets called once per vertex.
	TransformShape(Shape shape, std::function<void(ShapeVertex&)> mutate) :
		shape_{std::move(shape)},
		mutate_{mutate}
	{

	}

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return shape_.edges(); }

	Vertices vertices() const noexcept { return *this; }

private:

	std::function<void(ShapeVertex&)> mutate_;

};


template <typename Shape>
TransformShape<Shape> transformShape(
	Shape shape, std::function<void(ShapeVertex&)> mutate
) {
	return TransformShape<Shape>{std::move(shape), std::move(mutate)};
}


}


#endif
