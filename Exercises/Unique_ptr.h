#pragma once

#include "Common.h"

/*  std::unique_ptr is a smart pointer that owns and manages another object through a pointer
    and disposes of that object when the unique_ptr goes out of scope.
 */

class UniqueBase {
public:
    virtual void bar() { std::cout << "UniqueBase::bar\n"; }
    virtual ~UniqueBase() = default;
};

class UniqueDerived : public UniqueBase
{
public:
    UniqueDerived() { std::cout << "UniqueDerived::UniqueDerived\n"; }
    ~UniqueDerived() { std::cout << "UniqueDerived::~UniqueDerived\n"; }
    void bar() override { std::cout << "UniqueDerived::bar\n"; }
};

/* a function consuming a unique_ptr can take it by value or by rvalue reference */
std::unique_ptr<UniqueDerived> pass_through(std::unique_ptr<UniqueDerived> p)
{
    p->bar();
    return p;
}