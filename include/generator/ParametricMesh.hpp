// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_PARAMETRICMESH_HPP
#define GENERATOR_PARAMETRICMESH_HPP

#include <functional>


#include "Triangle.hpp"
#include "MeshVertex.hpp"


namespace generator {


/// A mesh with values evaluated using a callback function.
class ParametricMesh {
public:

	class Triangles {
	public:

		Triangle generate() const;
		bool done() const noexcept;
		void next();

	private:

		Triangles(const ParametricMesh& mesh);

		const ParametricMesh* mesh_;

		gml::ivec2 i_;

		bool even_;

	friend class ParametricMesh;
	};

	class Vertices {
	public:

		MeshVertex generate() const;
		bool done() const noexcept;
		void next();

	private:

		Vertices(const ParametricMesh& mesh);

		const ParametricMesh* mesh_;

		gml::ivec2 i_;

	friend class ParametricMesh;
	};


	/// @param eval A callback that returns a MeshVertex for a given value.
	/// @param segments The number of segments along the surface.
	/// Both should be >= 1. If either is zero an empty mesh is generated.
	explicit ParametricMesh(
		std::function<MeshVertex(const gml::dvec2& t)> eval,
		const gml::ivec2& segments = {16, 16}
	) noexcept;

	Triangles triangles() const noexcept;

	Vertices vertices() const noexcept;

private:

	std::function<MeshVertex(const gml::dvec2& t)> eval_;

	gml::ivec2 segments_;

	gml::dvec2 delta_;

};


}

#endif
