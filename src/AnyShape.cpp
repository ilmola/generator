// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#include "generator/AnyShape.hpp"


using namespace generator;


AnyShape::Base::~Base() { }


AnyShape::AnyShape(const AnyShape& that) :
	base_{that.base_->clone()}
{ }


AnyShape& AnyShape::operator=(const AnyShape& that) {
	base_ = that.base_->clone();
	return *this;
}


AnyGenerator<Edge> AnyShape::edges() const noexcept {
	return base_->edges();
}


AnyGenerator<ShapeVertex> AnyShape::vertices() const noexcept {
	return base_->vertices();
}


