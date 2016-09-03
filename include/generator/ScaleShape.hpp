// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_SCALESHAPE_HPP
#define GENERATOR_SCALESHAPE_HPP

#include "TransformShape.hpp"


namespace generator {


/// Scales a shape keeping tangents unit length.
template <typename Shape>
class ScaleShape
{
private:

	using Impl = TransformShape<Shape>;
	Impl transformShape_;

public:

	/// @param shape Source data shape.
	/// @param scale Scale factor.
	ScaleShape(Shape shape, const gml::dvec2& scale) :
		transformShape_{
			std::move(shape),
			[scale] (ShapeVertex& value) { 
				value.position *= scale; 
				value.tangent = normalize(scale * value.tangent);
			}
		}
	{ }

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return transformShape_.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformShape_.vertices(); }

};


template <typename Shape>
ScaleShape<Shape> scaleShape(Shape shape, const gml::dvec2& scale) {
	return ScaleShape<Shape>{std::move(shape), scale};
}

}

#endif

