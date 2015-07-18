// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_MERGEPath_HPP
#define GENERATOR_MERGEPath_HPP


#include "PathVertex.hpp"
#include "EmptyPath.hpp"
#include "utils.hpp"

namespace generator {


/// Merges (concatenates) multiple paths together.
template <typename... Path>
class MergePath; // undefined


template <>
class MergePath<> : public EmptyPath { };


template <typename Head, typename... Tail>
class MergePath<Head, Tail...> {
public:

	class Edges {
	public:

		Edge generate() const {
			if (!head_.done()) return head_.generate();
			return tail_.generate() + head_VertexCount;
		}

		bool done() const noexcept { return head_.done() && tail_.done(); }

		void next() {
			if (!head_.done()) head_.next();
			else tail_.next();
		}

		void reset() noexcept {
			head_.reset();
			tail_.reset();
		}

	private:

		typename EdgeGeneratorType<Head>::type  head_;
		typename EdgeGeneratorType<MergePath<Tail...>>::type tail_;

		unsigned head_VertexCount;

		Edges(const MergePath& path) :
			head_{path.head_.triangles()},
			tail_(path.tail_.triangles()),
			head_VertexCount{count(path.head_.vertices())}
		{ }

	friend class MergePath<Head, Tail...>;
	};


	class Vertices {
	public:

		PathVertex generate() const {
			if (!head_.done()) return head_.generate();
			return tail_.generate();
		}

		bool done() const noexcept { return head_.done() && tail_.done(); }

		void next() {
			if (!head_.done()) head_.next();
			else tail_.next();
		}

		void reset() noexcept {
			head_.reset();
			tail_.reset();
		}

	private:

		typename VertexGeneratorType<Head>::type head_;
		typename VertexGeneratorType<MergePath<Tail...>>::type tail_;

		Vertices(const MergePath& path) :
			head_{path.head_.vertices()},
			tail_(path.tail_.vertices())
		{ }

	friend class MergePath<Head, Tail...>;
	};



	MergePath(Head head, Tail... tail) :
		head_{head},
		tail_{tail...}
	{ }

	Edges edges() const noexcept { return *this; }

	Vertices vertices() const noexcept { return *this; }


private:

	Head head_;
	MergePath<Tail...> tail_;

};



template <typename... Path>
MergePath<Path...> mergePath(Path... paths) {
	return MergePath<Path...>{std::move(paths)...};
}

}

#endif
