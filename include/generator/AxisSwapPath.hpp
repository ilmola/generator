// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_AXISSWAPPATH_HPP
#define GENERATOR_AXISSWAPPATH_HPP

#include "Axis.hpp"
#include "TransformPath.hpp"

namespace generator {



/// Swaps axis in path.
template <typename Path>
class AxisSwapPath
{
private:

	using Impl = TransformPath<Path>;
	Impl transformPath_;

public:

	/// @param path Source data path
	/// @param x Axis to use as the X-axis
	/// @param y Axis to use as the Y-axis
	/// @param z Axis to use as the Z-axis
	AxisSwapPath(Path path, Axis x, Axis y, Axis z) :
		transformPath_{
			std::move(path),
			[x, y, z] (PathVertex& vertex) {
				vertex.position	= gml::dvec3{
					vertex.position[static_cast<int>(x)],
					vertex.position[static_cast<int>(y)],
					vertex.position[static_cast<int>(z)]
				};
				vertex.tangent = gml::dvec3{
					vertex.tangent[static_cast<int>(x)],
					vertex.tangent[static_cast<int>(y)],
					vertex.tangent[static_cast<int>(z)]
				};
				vertex.normal = gml::dvec3{
					vertex.normal[static_cast<int>(x)],
					vertex.normal[static_cast<int>(y)],
					vertex.normal[static_cast<int>(z)]
				};
			}
		}
	{ }

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return transformPath_.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformPath_.vertices(); }

};


template <typename Path>
AxisSwapPath<Path> axisSwapPath(Path path, Axis x, Axis y, Axis z) {
	return AxisSwapPath<Path>{std::move(path), x, y, z};
}


}


#endif

