#ifndef HashTableItem_h
#define HashTableItem_h

#include "common.h"

struct HashTableItem {
	HashTableItem(string key, Contact *c = 0);

	string key;
	vector<Contact *> values;
};

#endif
