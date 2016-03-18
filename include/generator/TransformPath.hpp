// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_TRANSFORMPATH_HPP
#define GENERATOR_TRANSFORMPATH_HPP

#include <functional>

#include "PathVertex.hpp"
#include "utils.hpp"


namespace generator {


/// Apply a mutator function to each vertex.
template <typename Path>
class TransformPath :
	private Path
{
public:

	class Vertices {
	public:

		PathVertex generate() const {
			auto vertex = vertices_.generate();
			path_->mutate_(vertex);
			return vertex;
		}

		bool done() const noexcept { return vertices_.done(); }

		void next() { vertices_.next(); }

	private:

		Vertices(const TransformPath& path) :
			path_{&path},
			vertices_{static_cast<const Path&>(path).vertices()}
		{ }

		const TransformPath* path_;

		typename VertexGeneratorType<Path>::Type vertices_;

	friend class TransformPath;
	};

	/// @param path Source data path.
	/// @param mutate Callback function that gets called once per vertex.
	TransformPath(Path path, std::function<void(PathVertex&)> mutate) :
		Path{std::move(path)},
		mutate_{mutate}
	 { }

	Vertices vertices() const noexcept { return*this; }

	using Path::edges;

private:

	std::function<void(PathVertex&)> mutate_;

};


template <typename Path>
TransformPath<Path> transformPath(
	Path path, std::function<void(PathVertex&)> mutate
) {
	return TransformPath<Path>{std::move(path), std::move(mutate)};
}


}

#endif
