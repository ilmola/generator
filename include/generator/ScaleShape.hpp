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
class ScaleShape :
	private TransformShape<Shape>
{
public:

	/// @param shape Source data shape.
	/// @param scale Scale factor.
	ScaleShape(Shape shape, const gml::dvec2& scale) :
		TransformShape<Shape>{
			std::move(shape),
			[scale] (ShapeVertex& value) { 
				value.position *= scale; 
				value.tangent = normalize(scale * value.tangent);
			}
		}
	{ }

	using TransformShape<Shape>::edges;

	using TransformShape<Shape>::vertices;

};


template <typename Shape>
ScaleShape<Shape> scaleShape(Shape shape, const gml::dvec2& scale) {
	return ScaleShape<Shape>{std::move(shape), scale};
}

}

#endif

