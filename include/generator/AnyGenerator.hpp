// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_ANYGENERATOR_HPP
#define GENERATOR_ANYGENERATOR_HPP

#include <memory>


namespace generator {


/// A type erasing container that can store any generator that generates type T.
/// @tparam T Type returned by the generate() -function.
template <typename T>
class AnyGenerator
{
public:

	template <typename Generator>
	AnyGenerator(Generator generator) :
		base_{new Derived<Generator>{std::move(generator)}}
	{ }

	AnyGenerator(const AnyGenerator& that) : base_{that.base_->clone()} { }

	AnyGenerator(AnyGenerator&&) = default;

	AnyGenerator& operator=(const AnyGenerator& that) {
		base_ = that.base_->clone();
		return *this;
	}

	AnyGenerator& operator=(AnyGenerator&&) = default;

	T generate() const { return base_->generate(); }

	bool done() const noexcept { return base_->done(); }

	void next() { base_->next(); }

private:

	class Base {
	public:
		virtual ~Base() { }
		virtual std::unique_ptr<Base> clone() const = 0;
		virtual T generate() const = 0;
		virtual bool done() const noexcept = 0;
		virtual void next() = 0;
	};

	template <typename Generator>
	class Derived : public Base {
	public:

		Derived(Generator generator) : generator_{std::move(generator)} { }

		virtual std::unique_ptr<Base> clone() const override {
			return std::unique_ptr<Base>(new Derived{generator_});
		}

		virtual T generate() const override {
			return generator_.generate();
		}

		virtual bool done() const noexcept override {
			return generator_.done();
		}

		virtual void next() override {
			generator_.next();
		}

	private:

		Generator generator_;

	};

	std::unique_ptr<Base> base_;

};

}


#endif
