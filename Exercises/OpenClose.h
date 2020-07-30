#pragma once

#include "Header.h"

/* Concept - open for extension, close for modification */

enum class Color 
{ 
	Red, 
	Green, 
	Blue 
};

enum class Size 
{ 
	Small, 
	Medium, 
	Large 
};

class Product
{
public:
	string	name;
	Color	color;
	Size	size;
};

/* This is a WRONG way to implement */
class ProductFilter
{
public:
	typedef vector<Product*> Items;	
	// {

		/* filter by color */
		Items by_color(Items items,Color color)
		{
			Items result;
			for (auto& i : items)
				if (i->color == color)
					result.push_back(i);
			return result;
		}
	
		/* filter by size */
		Items by_color(Items items, Size size)
		{
			Items result;
			for (auto& i : items)
				if (i->size == size)
					result.push_back(i);
			return result;
		}

		/* filter by color and size */
		Items by_color_and_size(Items items, Size size, Color color)
		{
			Items result;
			for (auto& i : items)
				if (i->size == size && i->color == color)
					result.push_back(i);
			return result;
		}
	// }
};

/* The Right way to handle */
/* Separate the responsibility to handle open and close */
template <typename T> 
class Specification
{
public:
	virtual bool is_satisfied(T* item) = 0;
};

template <typename T> 
class Filter
{
public:
	virtual vector<T*> filter( vector<T*> items, Specification<T>& spec) = 0;
};

class BetterFilter : public Filter<Product>
{
public:
	vector<Product*> filter( vector<Product*> items, Specification<Product>& spec) override
	{
		vector<Product*> result;
		for (auto& p : items) 
		{
			if (spec.is_satisfied(p))
				result.push_back(p);
		}
		return result;
	}
};

class ColorSpecification : public Specification<Product>
{
public:
	Color color;
	explicit ColorSpecification(const Color color) : color{ color } {}
	
	bool is_satisfied(Product* item) override 
	{
		return item->color == color;
	}
};

class SizeSpecification : public Specification<Product>
{
public:
	Size size;
	explicit SizeSpecification(const Size size) : size{ size } {}

	bool is_satisfied(Product* item) override
	{
		return item->size == size;
	}
};

template <typename T> struct MultipleSpecification : Specification<T>
{
	Specification<T>& first;
	Specification<T>& second;
	MultipleSpecification(Specification<T>& first, Specification<T>& second)	: first{ first }, second{ second } {}

	bool is_satisfied(T* item) override
	{
		return first.is_satisfied(item) &&
			second.is_satisfied(item);
	}
};