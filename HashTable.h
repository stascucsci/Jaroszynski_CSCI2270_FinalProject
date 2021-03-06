#ifndef HashTable_h
#define HashTable_h

#include "common.h"

class HashTable {
public:
	HashTable(int size_);
	~HashTable();
	void addItem(string key, Contact *value);
	void removeItem(string key, Contact *value);
	vector<Contact *> findItem(string key);
	void clear();
	void print();

private:
	int size;
	vector<HashTableItem> *data;

	int getHash(string s) const;
};

#endif
