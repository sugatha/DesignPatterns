#pragma once
#include "Common.h"

class Person
{
	int		age_;
	string	name_;
public:
	int		get_age() const { return age_; }
	void	set_age(int value) { age_ = value; }

	string	get_name() const { return name_; }
	void	set_name(string value) { name_ = value; }


	/* using the non standard declartion - property  - to implement - get and a set */
	__declspec(property(get = get_age, put = set_age)) int age;
	__declspec(property(get = get_name, put = set_name)) string name;
};
