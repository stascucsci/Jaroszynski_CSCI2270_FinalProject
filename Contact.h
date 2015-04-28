#ifndef Contact_h
#define Contact_h

#include "common.h"

struct Contact {
	Contact(string first = "",
			string last = "",
			string state_ = "",
			string phone_ = "",
			int age_ = 0)
		: firstName(first),
		lastName(last),
		phone(phone_),
		state(state_),
		age(age_) {}

	void print();

	string firstName;
	string lastName;
	string phone;
	string state;
	
	int age;
};

#endif
