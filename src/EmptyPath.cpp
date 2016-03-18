// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.


#include "generator/EmptyPath.hpp"


using namespace generator;



Edge EmptyPath::Edges::generate() const {
	throw std::out_of_range("Called generate on an EmptyPath!");
}

bool EmptyPath::Edges::done() const noexcept {
	return true;
}

void EmptyPath::Edges::next() {
	throw std::out_of_range("Called next on an EmptyPath!");
}



EmptyPath::Edges::Edges() {}




PathVertex EmptyPath::Vertices::generate() const {
	throw std::out_of_range("Called generate on an EmptyPath!");
}

bool EmptyPath::Vertices::done() const noexcept {
	return true;
}

void EmptyPath::Vertices::next() {
	throw std::out_of_range("Called next on an EmptyPath!");
}


EmptyPath::Vertices::Vertices() { }


EmptyPath::EmptyPath() {}

EmptyPath::Edges EmptyPath::edges() const noexcept {
	return {};
}

EmptyPath::Vertices EmptyPath::vertices() const noexcept {
	return {};
}



