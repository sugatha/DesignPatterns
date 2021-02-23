#pragma once

#include "Common.h"

template <class T>
T const& findmax(T const& a, T const& b)
{
	return a < b ? b : a;
}