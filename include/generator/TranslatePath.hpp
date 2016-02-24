// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_TRANSLATEPATH_HPP
#define GENERATOR_TRANSLATEPATH_HPP

#include "math.hpp"

#include "TransformPath.hpp"

namespace generator {


/// Translates the position of each vertex by given amount.
template <typename Path>
class TranslatePath :
	private TransformPath<Path>
{
public:

	/// @param path Source data path.
	/// @param delta Amount to increment each vertex position.
	TranslatePath(Path path, const gml::dvec3& delta) :
		TransformPath<Path>{
			std::move(path),
			[delta] (PathVertex& value) { value.position += delta;	}
		}
	{ }

	using TransformPath<Path>::edges;

	using TransformPath<Path>::vertices;

};


template <typename Path>
TranslatePath<Path> translatePath(Path path, const gml::dvec3& delta) {
	return TranslatePath<Path>{std::move(path), delta};
}

}

#endif
