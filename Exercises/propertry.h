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

	// NOTE: Member - The operator can either be a friend or a const

	/*friend bool operator < (const Person & pLhs, const Person & pRhs) { 
		return ((((pLhs.age_ == pRhs.age_) || (pLhs.age_ < pRhs.age_)) && (pLhs.name_ < pRhs.name_)) ? 1:0);
	}
	friend bool operator > (const Person& pLhs, const Person& pRhs) {
		return ((((pLhs.age_ == pRhs.age_) || (pLhs.age_ < pRhs.age_)) && (pLhs.name_ > pRhs.name_)) ? 1 : 0);
	}*/

	// NOTE: Member - non friend
	/*bool operator < (const Person& pRhs) const {
		return ((((this->age_ == pRhs.age_) || (this->age_ < pRhs.age_)) && (this->name_ < pRhs.name_)) ? 1 : 0);
	}
	bool operator > (const Person& pRhs) const {
		return ((((this->age_ == pRhs.age_) || (this->age_ < pRhs.age_)) && (this->name_ > pRhs.name_)) ? 1 : 0);
	}*/

	/* using the non standard declartion - property  - to implement - get and a set */
	__declspec(property(get = get_age, put = set_age)) int age;
	__declspec(property(get = get_name, put = set_name)) string name;
};

// NOTE: Nonfriend, Non Member - This is a better way - segregating the comparison
bool operator < (const Person& pLhs, const Person& pRhs) {
	return ((((pLhs.age == pRhs.age) || (pLhs.age < pRhs.age)) && (pLhs.name < pRhs.name)) ? 1 : 0);
}
bool operator > (const Person& pLhs, const Person& pRhs) {
	return ((((pLhs.age == pRhs.age) || (pLhs.age < pRhs.age)) && (pLhs.name > pRhs.name)) ? 1 : 0);
}
