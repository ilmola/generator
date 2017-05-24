// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_MERGESHAPE_HPP
#define GENERATOR_MERGESHAPE_HPP


#include "ShapeVertex.hpp"
#include "EmptyShape.hpp"
#include "utils.hpp"

namespace generator {


/// Merges (concatenates) multiple shapes together.
template <typename... Shape>
class MergeShape; // undefined


template <>
class MergeShape<> : public EmptyShape { };


template <typename Head, typename... Tail>
class MergeShape<Head, Tail...> {
public:

	class Edges {
	public:

		Edge generate() const {
			if (!head_.done()) return head_.generate();

			Edge edge = tail_.generate();
			edge.vertices += head_VertexCount;
			return edge;
		}

		bool done() const noexcept { return mAllDone; }

		void next() {
			if (!head_.done()) head_.next();
			else tail_.next();

			mAllDone = tail_.done() && head_.done();
		}

	private:

		typename EdgeGeneratorType<Head>::Type  head_;
		typename EdgeGeneratorType<MergeShape<Tail...>>::Type tail_;

		int head_VertexCount;

		bool mAllDone;

		Edges(const MergeShape& shape) :
			head_{shape.head_.edges()},
			tail_(shape.tail_.edges()),
			head_VertexCount{count(shape.head_.vertices())},
			mAllDone{tail_.done() && head_.done()}
		{ }

	friend class MergeShape<Head, Tail...>;
	};


	class Vertices {
	public:

		ShapeVertex generate() const {
			if (!head_.done()) return head_.generate();
			return tail_.generate();
		}

		bool done() const noexcept { return mAllDone; }

		void next() {
			if (!head_.done()) head_.next();
			else tail_.next();

			mAllDone = tail_.done() && head_.done();
		}

	private:

		typename VertexGeneratorType<Head>::Type head_;
		typename VertexGeneratorType<MergeShape<Tail...>>::Type tail_;
		bool mAllDone;

		Vertices(const MergeShape& shape) :
			head_{shape.head_.vertices()},
			tail_(shape.tail_.vertices()),
			mAllDone{tail_.done() && head_.done()}
		{ }

	friend class MergeShape<Head, Tail...>;
	};



	MergeShape(Head head, Tail... tail) :
		head_{head},
		tail_{tail...}
	{ }

	Edges edges() const noexcept { return *this; }

	Vertices vertices() const noexcept { return *this; }


private:

	Head head_;
	MergeShape<Tail...> tail_;

};



template <typename... Shape>
MergeShape<Shape...> mergeShape(Shape... shapes) {
	return MergeShape<Shape...>{std::move(shapes)...};
}

}

#endif


