// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ANYPATH_HPP
#define GENERATOR_ANYPATH_HPP

#include <memory>

#include "AnyGenerator.hpp"
#include "Edge.hpp"
#include "PathVertex.hpp"


namespace generator {


/// A type erasing container that can store any path.
class AnyPath
{
public:

	template <typename Path>
	AnyPath(Path path) :
		base_{new Derived<Path>{std::move(path)}}
	{ }

	AnyPath(const AnyPath& that);

	AnyPath(AnyPath&&) = default;

	AnyPath& operator=(const AnyPath& that);

	AnyPath& operator=(AnyPath&&) = default;

	AnyGenerator<Edge> edges() const noexcept;

	AnyGenerator<PathVertex> vertices() const noexcept;

private:

	class Base {
	public:
		virtual ~Base();
		virtual std::unique_ptr<Base> clone() const = 0;
		virtual AnyGenerator<Edge> edges() const = 0;
		virtual AnyGenerator<PathVertex> vertices() const = 0;
	};

	template <typename Path>
	class Derived : public Base {
	public:
		Derived(Path path) : path_(std::move(path)) { }

		virtual std::unique_ptr<Base> clone() const override {
			return std::unique_ptr<Base>{new Derived{path_}};
		}

		virtual AnyGenerator<Edge> edges() const override {
			return path_.edges();
		}

		virtual AnyGenerator<PathVertex> vertices() const override {
			return path_.vertices();
		}

		Path path_;
	};

	std::unique_ptr<Base> base_;

};

}


#endif
