// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ANYMESH_HPP
#define GENERATOR_ANYMESH_HPP

#include <memory>

#include "AnyGenerator.hpp"
#include "MeshVertex.hpp"
#include "Triangle.hpp"


namespace generator {


/// A type erasing container that can store any mesh.
class AnyMesh 
{
public:

	template <typename Mesh>
	AnyMesh(Mesh mesh) :
		base_{new Derived<Mesh>{std::move(mesh)}}
	{ }

	AnyMesh(const AnyMesh& that);

	AnyMesh(AnyMesh&&) = default;

	AnyMesh& operator=(const AnyMesh& that);

	AnyMesh& operator=(AnyMesh&&) = default;

	AnyGenerator<Triangle> triangles() const noexcept;

	AnyGenerator<MeshVertex> vertices() const noexcept;

private:

	class Base {
	public:
		virtual ~Base();
		virtual std::unique_ptr<Base> clone() const = 0;
		virtual AnyGenerator<Triangle> triangles() const = 0;
		virtual AnyGenerator<MeshVertex> vertices() const = 0;
	};

	template <typename Mesh>
	class Derived : public Base {
	public:

		Derived(Mesh mesh) : mesh_(std::move(mesh)) { }

		virtual std::unique_ptr<Base> clone() const override {
			return std::unique_ptr<Base>{new Derived{mesh_}};
		}

		virtual AnyGenerator<Triangle> triangles() const override { 
			return mesh_.triangles();
		}

		virtual AnyGenerator<MeshVertex> vertices() const override { 
			return mesh_.vertices();
		}

		Mesh mesh_;

	};

	std::unique_ptr<Base> base_;

};

}


#endif
