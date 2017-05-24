// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/ParametricPath.hpp"


using namespace generator;


ParametricPath::Edges::Edges(const ParametricPath& path) :
	path_{&path},
	i_{0}
{

}


Edge ParametricPath::Edges::generate() const {
	if (done()) throw std::out_of_range("Done!");
	return Edge{{i_, i_ + 1}};
}


bool ParametricPath::Edges::done() const noexcept {
	return i_ == path_->segments_;
}


void ParametricPath::Edges::next() {
	if (done()) throw std::out_of_range("Done!");
	++i_;
}




ParametricPath::Vertices::Vertices(const ParametricPath& path) :
	path_{&path},
	i_{0}
{ }



PathVertex ParametricPath::Vertices::generate() const {
	if (done()) throw std::out_of_range("Done!");

	return path_->eval_(i_ * path_->delta_);
}

bool ParametricPath::Vertices::done() const noexcept {
	if (path_->segments_ == 0) return true;
	return i_ == path_->segments_ + 1;
}

void ParametricPath::Vertices::next() {
	if (done()) throw std::out_of_range("Done!");
	++i_;
}





ParametricPath::ParametricPath(
	std::function<PathVertex(double)> eval,
	int segments
) noexcept :
	eval_{std::move(eval)},
	segments_{segments},
	delta_{1.0 / segments}
{ }


ParametricPath::Edges ParametricPath::edges() const noexcept {
	return *this;
}


ParametricPath::Vertices ParametricPath::vertices() const noexcept {
	return *this;
}


