// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_SHAPETOPATH_HPP
#define GENERATOR_SHAPETOPATH_HPP


#include "PathVertex.hpp"
#include "ShapeVertex.hpp"
#include "utils.hpp"


namespace generator {



/// Converts a Shape to a Path.
/// The shape position coordinates are used as the x and y and 0 is used as z.
/// Shape tangent becomes the path tangent and z-axis becomes normal vector and
/// thus the shape normal becomes the path binormal.
template <typename Shape>
class ShapeToPath
{
private:

	using Impl = Shape;
	Impl shape_;

public:

	class Vertices {
	public:

		PathVertex generate() const {

			ShapeVertex shapeVertex = vertices_.generate();

			PathVertex vertex;

			vertex.position = gml::dvec3(shapeVertex.position, 0.0);

			vertex.tangent = gml::dvec3(shapeVertex.tangent, 0.0);
			vertex.normal = gml::dvec3{0.0, 0.0, 1.0};

			vertex.texCoord = shapeVertex.texCoord;

			return vertex;
		}

		bool done() const noexcept { return vertices_.done(); }

		void next() { vertices_.next(); }

	private:

		typename VertexGeneratorType<Shape>::Type vertices_;

		Vertices(const Shape& shape) :
			vertices_{shape.vertices()}
		{ }

	friend class ShapeToPath;
	};

	ShapeToPath(Shape shape) :
		shape_{std::move(shape)}
	{ }

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return shape_.edges(); }

	Vertices vertices() const { return *this; }

};



template <typename Shape>
ShapeToPath<Shape> shapeToPath(Shape shape) {
	return ShapeToPath<Shape>{std::move(shape)};
}


}



#endif
