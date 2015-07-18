// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/AnyMesh.hpp"


using namespace generator;



AnyMesh::Base::~Base() { }


AnyMesh::AnyMesh(const AnyMesh& that) :
	base_{that.base_->clone()}
{ }


AnyMesh& AnyMesh::operator=(const AnyMesh& that) {
	base_ = that.base_->clone();
	return *this;
}


AnyGenerator<Triangle> AnyMesh::triangles() const noexcept {
	return base_->triangles();
}


AnyGenerator<MeshVertex> AnyMesh::vertices() const noexcept {
	return base_->vertices();
}

