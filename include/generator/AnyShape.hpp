// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ANYSHAPE_HPP
#define GENERATOR_ANYSHAPE_HPP

#include <memory>


#include "AnyGenerator.hpp"
#include "Edge.hpp"
#include "ShapeVertex.hpp"


namespace generator {


/// A type erasing container that can store any shape.
class AnyShape
{
public:

	template <typename Shape>
	AnyShape(Shape shape) :
		base_{new Derived<Shape>{std::move(shape)}}
	{ }

	AnyShape(const AnyShape& that);

	AnyShape(AnyShape&&) = default;

	AnyShape& operator=(const AnyShape& that);

	AnyShape& operator=(AnyShape&&) = default;

	AnyGenerator<Edge> edges() const noexcept;

	AnyGenerator<ShapeVertex> vertices() const noexcept;

private:

	class Base {
	public:
		virtual ~Base();
		virtual std::unique_ptr<Base> clone() const = 0;
		virtual AnyGenerator<Edge> edges() const = 0;
		virtual AnyGenerator<ShapeVertex> vertices() const = 0;
	};

	template <typename Shape>
	class Derived : public Base {
	public:

		Derived(Shape shape) : shape_(std::move(shape)) { }

		virtual std::unique_ptr<Base> clone() const override {
			return std::unique_ptr<Base>{new Derived{shape_}};
		}

		virtual AnyGenerator<Edge> edges() const override {
			return shape_.edges();
		}

		virtual AnyGenerator<ShapeVertex> vertices() const override {
			return shape_.vertices();
		}

		Shape shape_;
	};

	std::unique_ptr<Base> base_;

};

}


#endif
