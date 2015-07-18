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
class ScalePath :
	private TransformPath<Path>
{
public:

	/// @param path Source data path.
	/// @param scale Scale Factor. Must not have zero components!
	ScalePath(Path path, const gml::dvec3& scale) :
		TransformPath<Path>{
			std::move(path),
			[scale] (PathVertex& value) { 
				value.position *= scale;
				value.tangent = gml::normalize(scale * value.tangent);
				value.normal = gml::normalize(scale * value.normal);  
			}
		}
	{ }

	using TransformPath<Path>::edges;

	using TransformPath<Path>::vertices;

};


template <typename Path>
ScalePath<Path> scalePath(Path path, const gml::dvec3& scale) {
	return ScalePath<Path>{std::move(path), scale};
}

}

#endif
