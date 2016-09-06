// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_SCALEPATH_HPP
#define GENERATOR_SCALEPATH_HPP

#include "TransformPath.hpp"


namespace generator {


/// Scales a path. Keeps tangents and normals unit length.
template <typename Path>
class ScalePath
{
private:

	using Impl = TransformPath<Path>;
	Impl transformPath_;

public:

	/// @param path Source data path.
	/// @param scale Scale Factor. Must not have zero components!
	ScalePath(Path path, const gml::dvec3& scale) :
		transformPath_{
			std::move(path),
			[scale] (PathVertex& value) { 
				value.position *= scale;
				value.tangent = gml::normalize(scale * value.tangent);
				value.normal = gml::normalize(scale * value.normal);  
			}
		}
	{ }

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return transformPath_.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformPath_.vertices(); }

};


template <typename Path>
ScalePath<Path> scalePath(Path path, const gml::dvec3& scale) {
	return ScalePath<Path>{std::move(path), scale};
}

}

#endif
