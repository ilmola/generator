// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_FLIPPATH_HPP
#define GENERATOR_FLIPPATH_HPP


#include "Edge.hpp"
#include "TransformPath.hpp"


namespace generator {


/// Flips mesh inside out. Reverses triangles and normals.
template <typename Path>
class FlipPath
{
private:

	using Impl = TransformPath<Path>;
	Impl transformPath_;

public:

	class Edges {
	public:

		Edge generate() const {
			Edge edge = edges_.generate();
			std::swap(edge.vertices[0], edge.vertices[1]);
			return edge;
		}

		bool done() const noexcept { return edges_.done(); }

		void next() { edges_.next(); }

	private:

		typename EdgeGeneratorType<TransformPath<Path>>::Type edges_;

		Edges(const TransformPath<Path>& path) :
			edges_{path.edges()}
		{ }

	friend class FlipPath;
	};

	/// @param path Source data path.
	FlipPath(Path path) :
		transformPath_{
			std::move(path),
			[] (PathVertex& vertex) {
				vertex.tangent *= -1.0;
				vertex.normal *= -1.0;
			}
		}
	{ }

	Edges edges() const noexcept { return {*this}; }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformPath_.vertices(); }


};


template <typename Path>
FlipPath<Path> flipPath(Path path) {
	return FlipPath<Path>{std::move(path)};
}


}



#endif
