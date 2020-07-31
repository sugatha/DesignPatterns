#pragma once
#include "Common.h"

struct Foo
{
	Foo(int n) {}
	Foo(const Foo&) { cout << "COPY CONSTRUCTOR!!!\n"; }
};

/* in some compilers copy ctor will be called */
/*Foo make_foo(int n)
{
	return Foo{ n };
}*/

/* Safer to use unique_ptr */
unique_ptr<Foo> make_foo(int n)
{
	return make_unique<Foo>(n);
}