// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ROTATEPATH_HPP
#define GENERATOR_ROTATEPATH_HPP

#include "Axis.hpp"
#include "TransformPath.hpp"


namespace generator {


/// Rotates vertices, tangents and normals.
template <typename Path>
class RotatePath
{
private:

	using Impl = TransformPath<Path>;
	Impl transformPath_;

public:

	RotatePath(Path path, const gml::dquat& rotation) :
		transformPath_{
			std::move(path),
			[rotation] (PathVertex& value) {
				value.position = gml::transform(rotation, value.position);
				value.normal = gml::transform(rotation, value.normal);
			}
		}
	{ }

	RotatePath(Path path, double angle, const gml::dvec3& axis) :
		RotatePath{std::move(path), gml::qrotate(angle, axis)}
	{ }

	RotatePath(Path path, double angle, Axis axis) :
		RotatePath{
			std::move(path),
			gml::qrotate(
				angle,
				axis == Axis::X ?
					gml::dvec3{1.0, 0.0, 0.0} :
					(axis == Axis::Y ? gml::dvec3{0.0, 1.0, 0.0} : gml::dvec3{0.0, 0.0, 1.0})
			)
		}
	{ }

	using Edges = typename Impl::Edges;

	Edges edges() const noexcept { return transformPath_.edges(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformPath_.vertices(); }

};


template <typename Path>
RotatePath<Path> rotatePath(Path path, const gml::dquat& rotation) {
	return RotatePath<Path>{std::move(path), rotation};
}


template <typename Path>
RotatePath<Path> rotatePath(Path path, double angle, const gml::dvec3& axis) {
	return RotatePath<Path>{std::move(path), angle, axis};
}


template <typename Path>
RotatePath<Path> rotatePath(Path path, double angle, Axis axis) {
	return RotatePath<Path>{std::move(path), angle, axis};
}


}


#endif
