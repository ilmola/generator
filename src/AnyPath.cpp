// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#include "generator/AnyPath.hpp"


using namespace generator;


AnyPath::Base::~Base() { }


AnyPath::AnyPath(const AnyPath& that) :
	base_{that.base_->clone()}
{ }


AnyPath& AnyPath::operator=(const AnyPath& that) {
	base_ = that.base_->clone();
	return *this;
}


AnyGenerator<Edge> AnyPath::edges() const noexcept {
	return base_->edges();
}


AnyGenerator<PathVertex> AnyPath::vertices() const noexcept {
	return base_->vertices();
}
