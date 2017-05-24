// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/ParametricMesh.hpp"


using namespace generator;


ParametricMesh::Triangles::Triangles(const ParametricMesh& mesh) :
	mesh_{&mesh},
	i_{0},
	even_{false}
{ }


Triangle ParametricMesh::Triangles::generate() const {
	if (done()) throw std::out_of_range("Done!");

	Triangle triangle;

	const int base = i_[1] * (mesh_->segments_[0] + 1) + i_[0];

	if (!even_) {
		triangle.vertices = {
			base,
			base + 1,
			base + mesh_->segments_[0] + 1
		};
	}
	else {
		triangle.vertices = {
			base + 1,
			base + mesh_->segments_[0] + 2,
			base + mesh_->segments_[0] + 1
		};
	}

	return triangle;
}

bool ParametricMesh::Triangles::done() const noexcept {
	if (mesh_->segments_[0] == 0 || mesh_->segments_[1] == 0) return true;
	return i_[1] == mesh_->segments_[1];
}

void ParametricMesh::Triangles::next() {
	if (done()) throw std::out_of_range("Done!");

	even_ = !even_;

	if (!even_) {
		++i_[0];
		if (i_[0] == mesh_->segments_[0]) {
			i_[0] = 0;
			++i_[1];
		}
	}
}




ParametricMesh::Vertices::Vertices(const ParametricMesh& mesh) :
	mesh_{&mesh}, i_{0}
{ }



MeshVertex ParametricMesh::Vertices::generate() const {
	if (done()) throw std::out_of_range("Done!");

	return mesh_->eval_({i_[0] * mesh_->delta_[0], i_[1] * mesh_->delta_[1]});
}


bool ParametricMesh::Vertices::done() const noexcept {
	if (mesh_->segments_[0] == 0 || mesh_->segments_[1] == 0) return true;
	return i_[1] > mesh_->segments_[1];
}


void ParametricMesh::Vertices::next() {
	if (done()) throw std::out_of_range("Done!");

	++i_[0];
	if (i_[0] > mesh_->segments_[0]) {
		i_[0] = 0;
		++i_[1];
	}
}




ParametricMesh::ParametricMesh(
	std::function<MeshVertex(const gml::dvec2& t)> eval,
	const gml::ivec2& segments
) noexcept :
	eval_{std::move(eval)},
	segments_{segments},
	delta_{1.0 / segments[0], 1.0 / segments[1]}
{ }


ParametricMesh::Triangles ParametricMesh::triangles() const noexcept {
	return *this;
}


ParametricMesh::Vertices ParametricMesh::vertices() const noexcept {
	return *this;
}

