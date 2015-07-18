// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_PARAMETRICSHAPE_HPP
#define GENERATOR_PARAMETRICSHAPE_HPP

#include <functional>


#include "Edge.hpp"
#include "ShapeVertex.hpp"

namespace generator {


/// A shape with values evaluated using a callback function.
class ParametricShape {
public:

	class Edges {
	public:

		Edge generate() const;
		bool done() const noexcept;
		void next();
		void reset() noexcept;

	private:

		Edges(const ParametricShape& shape);

		const ParametricShape* shape_;

		unsigned i_;

	friend class ParametricShape;
	};

	class Vertices {
	public:

		ShapeVertex generate() const;
		bool done() const noexcept;
		void next();
		void reset() noexcept;

	private:

		Vertices(const ParametricShape& shape);

		const ParametricShape* shape_;

		unsigned i_;

	friend class ParametricShape;
	};


	/// @param eval Callback that returns a ShapeVertex for given value.
	/// @param segments Number of subdivisions
	ParametricShape(
		std::function<ShapeVertex(double)> eval,
		unsigned segments = 16u
	);

	ParametricShape(const ParametricShape&) = default;
	ParametricShape(ParametricShape&&) = default;

	Edges edges() const noexcept;

	Vertices vertices() const noexcept;

private:

	std::function<ShapeVertex(double)> eval_;

	unsigned segments_;

	double delta_;

};


}

#endif
