// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/EmptyMesh.hpp"


using namespace generator;


EmptyMesh::Triangles::Triangles() { }

Triangle EmptyMesh::Triangles::generate() const {
	throw std::out_of_range("Called generate on an EmptyMesh!");
}

bool EmptyMesh::Triangles::done() const noexcept {
	return true;
}

void EmptyMesh::Triangles::next() {
	throw std::out_of_range("Called next on an EmptyMesh!");
}




EmptyMesh::Vertices::Vertices() { }

MeshVertex EmptyMesh::Vertices::generate() const {
	throw std::out_of_range("Called generate on an EmptyMesh!");
}

bool EmptyMesh::Vertices::done() const noexcept {
	return true;
}

void EmptyMesh::Vertices::next() {
	throw std::out_of_range("Called next on an EmptyMesh!");
}



EmptyMesh::EmptyMesh() {}

EmptyMesh::Triangles EmptyMesh::triangles() const noexcept {
	return {};
}

EmptyMesh::Vertices EmptyMesh::vertices() const noexcept {
	return {};
}

