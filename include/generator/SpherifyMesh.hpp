// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef SPHERIFYMESH_HPP
#define SPHERIFYMESH_HPP

#include "TransformMesh.hpp"


namespace generator {


/// Projects vertices on a sphere centered at origin.
template <typename Mesh>
class SpherifyMesh
{
private:

	using Impl = TransformMesh<Mesh>;
	Impl transformMesh_;

public:

	SpherifyMesh(Mesh mesh, double radius, double factor) :
		transformMesh_{
			std::move(mesh),
			[radius, factor] (MeshVertex& value) {
				 value.position = gml::mix(
					value.position, 
					radius * gml::normalize(value.position), 
					factor
				);
				value.normal = gml::normalize(gml::mix(
					value.normal, 
					gml::normalize(value.position), 
					factor
				));
			}
		}
	{ }

	using Triangles = typename Impl::Triangles;

	Triangles triangles() const noexcept { return transformMesh_.triangles(); }

	using Vertices = typename Impl::Vertices;

	Vertices vertices() const noexcept { return transformMesh_.vertices(); }

};


template <typename Mesh>
SpherifyMesh<Mesh> spherifyMesh(Mesh mesh, double radius, double factor) {
	return SpherifyMesh<Mesh>{std::move(mesh), radius, factor};
}

}

#endif

