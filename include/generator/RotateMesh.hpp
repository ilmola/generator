// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ROTATEMESH_HPP
#define GENERATOR_ROTATEMESH_HPP

#include "Axis.hpp"
#include "TransformMesh.hpp"


namespace generator {


/// Rotates vertices and normals.
template <typename Mesh>
class RotateMesh
{
private:

	using Impl = TransformMesh<Mesh>;
	Impl transformMesh_;

public:

	/// @param mesh Source mesh data.
	/// @param rotation Quaternion presenting the rotation.
	RotateMesh(Mesh mesh, const gml::dquat& rotation) :
		transformMesh_{
			std::move(mesh),
			[rotation] (MeshVertex& value) {
				value.position = gml::transform(rotation, value.position);
				value.normal = gml::transform(rotation, value.normal);
			}
		}
	{ }

	/// @param mesh Source mesh data.
	/// @param angle Counterclockwise angle around the given axis.
	/// @param axis Unit length axis to rotate around.
	RotateMesh(Mesh mesh, double angle, const gml::dvec3& axis) :
		RotateMesh{std::move(mesh), gml::qrotate(angle, axis)}
	{ }

	RotateMesh(Mesh mesh, double angle, Axis axis) :
		RotateMesh{
			std::move(mesh),
			gml::qrotate(
				angle,
				axis == Axis::X ?
					gml::dvec3{1.0, 0.0, 0.0} :
					(axis == Axis::Y ? gml::dvec3{0.0, 1.0, 0.0} : gml::dvec3{0.0, 0.0, 1.0})
			)
		}
	{ }

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return transformMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformMesh_.vertices(); }

};


template <typename Mesh>
RotateMesh<Mesh> rotateMesh(Mesh mesh, const gml::dquat& rotation) {
	return RotateMesh<Mesh>{std::move(mesh), rotation};
}


template <typename Mesh>
RotateMesh<Mesh> rotateMesh(Mesh mesh, double angle, const gml::dvec3& axis) {
	return RotateMesh<Mesh>{std::move(mesh), angle, axis};
}


template <typename Mesh>
RotateMesh<Mesh> rotateMesh(Mesh mesh, double angle, Axis axis) {
	return RotateMesh<Mesh>{std::move(mesh), angle, axis};
}

}


#endif
