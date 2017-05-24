// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ITERATOR_HPP
#define GENERATOR_ITERATOR_HPP

#include <cassert>
#include <stdexcept>


#include "utils.hpp"


namespace generator {




/// An iterator that can be used to "drive" a generator.
/// Note that iterator mutates the generator.
template <typename Generator>
class Iterator
{
private:

	Generator* generator_;

	typename GeneratedType<Generator>::Type value_;

public:

	using iterator_category = std::input_iterator_tag;

	using value_type = typename GeneratedType<Generator>::Type;

	using difference_type = std::ptrdiff_t;

	using pointer = value_type*;

	using reference = value_type&;

	/// Creates a dummy end iterator.
	Iterator() noexcept :
		generator_{nullptr},
		value_{}
	{ }

	/// Iterator to the given generator.
	Iterator(Generator& generator) noexcept :
		generator_{&generator},
		value_{}
	{
		if (generator_->done()) generator_ = nullptr;
		else value_ = generator_->generate();
	}

	/// Advance the iterator.
	/// Might make the iterator "out of range".
	/// @throws std::out_of_range If the iterator is out of range.
	Iterator& operator++() {
		if (!generator_) throw std::out_of_range("Iterator out of range!");
		generator_->next();
		if (generator_->done()) generator_ = nullptr;
		else value_ = generator_->generate();
		return *this;
	}

	/// Get reference to the current generated value.
	/// @throws std::out_of_range If the iterator is out of range.
	const typename Iterator::value_type& operator*() const {
		if (!generator_) throw std::out_of_range("Iterator out of range!");
		return value_;
	}

	/// Get pointer to the current generated value.
	/// @throws std::out_of_range If the iterator is out of range
	const typename Iterator::value_type* operator->() const {
		if (!generator_) throw std::out_of_range("Iterator out of range!");
		return &value_;
	}

	/// Iterators are equal if both are out of range or both iterate the same
	/// generator.
	bool operator==(const Iterator& that) const noexcept {
		return generator_ == that.generator_;
	}

	bool operator!=(const Iterator& that) const noexcept {
		return generator_ != that.generator_;
	}

};


/// Will return an iterator to the generator.
template <typename Generator>
Iterator<Generator> begin(Generator& generator) noexcept {
	return Iterator<Generator>{generator};
}


/// Returns a dummy end iterator
template <typename Generator>
Iterator<Generator> end(const Generator&) noexcept {
	return Iterator<Generator>{};
}


}


#endif
