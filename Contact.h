#ifndef Contact_h
#define Contact_h

#include "common.h"

struct Contact {
	Contact(string first = "",
			string last = "",
			string phone_ = "",
			string addr = "",
			int age_ = 0)
		: firstName(first),
		lastName(last),
		phone(phone_),
		address(addr),
		age(age_) {}

	string firstName;
	string lastName;
	string phone;
	string address;
	
	int age;
};

#endif
