#include "HashTable.h"
#include "HashTableItem.h"

HashTable::HashTable(int size_)
	: size(size_), data(new vector<HashTableItem>[size]) {}

HashTable::~HashTable()
{
	delete [] data;
}

/*
	Function prototype:
	void HashTable::addItem(string, Contact *);

	Function description:
	Adds an entry to the hash table linking to the value based on the key.

	Example:
	HashTable h;
	h.addItem(new Contact());

	Pre-conditions: Unused entries in table are empty vectors. key nor value should be null/empty.
	Post-conditions: Item is added to table. If the key already exists, the value pointer is added to the already existing key.
*/
void HashTable::addItem(string key, Contact *value)
{
	if (key == "")
		return;
	int hash = getHash(key);
	for (int i = 0; i < data[hash].size(); i++) {
		if (data[hash][i].key == key) {
			data[hash][i].values.push_back(value);
			return;
		}
	}
	data[hash].push_back(HashTableItem(key, value));
}

/*
	Function prototype:
	void HashTable::removeItem(string, Contact *);

	Function description:
	Removes an item from the hash table.

	Example:
	HashTable t;
	Contact *c = new Contact("Hi");
	t.addItem(c->firstName, c);
	t.removeItem(c->firstName, c);

	Pre-conditions: value does not have to be in table in which case this does nothing. key nor value should be null/empty.
	Post-conditions: value is remove from table. If value was the only child of key, the key is also removed.
*/
void HashTable::removeItem(string key, Contact *value)
{
	int hash = getHash(key);
	for (int i = 0; i < data[hash].size(); i++) {
		for (int j = 0; j < data[hash][i].values.size(); j++) {
			if (data[hash][i].values[j] == value) {
				if (data[hash][i].values.size() == 1)
					data[hash].erase(data[hash].begin() + i);
				else
					data[hash][i].values.erase(data[hash][i].values.begin() + j);
				return;
			}
		}
	}
}

/*
	Function prototype:
	vector<Contact *> HashTable::findItem(string);

	Function description:
	Returns a vector of all the values that match the key

	Example:
	HashTable t;
	Contact *c = new Contact("Hi");
	t.addItem(c->firstName, c);
	t.findItem("Hi"); // returns vector<Contact *>(size=1) = {c}
	t.findItem("Bye"); // returns vector<Contact *>(size=0) = {}

	Pre-conditions: key must exist in table in order to be found
	Post-conditions: returns vector with matching vectors. Table is not modified.
*/
vector<Contact *> HashTable::findItem(string key)
{
	int hash = getHash(key);
	for (int i = 0; i < data[hash].size(); i++) {
		if (data[hash][i].key == key) {
			return data[hash][i].values;
		}
	}
	return vector<Contact *>();
}

/*
	Function prototype:
	int HashTable::getHash(string) const;

	Function description:
	Private;
	Computes the hash of the given string s using the djb2 algorithm.

	Example:
	this;
	string s = "Testing";
	this->getHash(s);


	Pre-conditions: none
	Post-conditions: returns positive int. Class is unchanged.
*/
int HashTable::getHash(string s) const
{
	unsigned long hash = 5381;
	for (int i = 0; i < s.length(); i++) {
		hash = ((hash << 5) + hash) + s[i];
	}
	return (unsigned int)hash % size;
}

void HashTable::print()
{
	for (int i = 0; i < size; i++) {
		if (data[i].size()) {
			cout << "[" << i << "] " << data[i][0].key;
			for (int j = 1; j < data[i].size(); j++)
				cout << "->" << data[i][j].key;
			cout << endl;
		}
	}
}

/*
	Function prototype:
	void HashTable::clear();

	Function description:
	Clears the hash table.

	Example:
	HashTable t;
	Contact *c = new Contact("Hi");
	t.addItem(c->firstName, c);
	t.clear;
	// t is now empty but c is unaltered.

	Pre-conditions: none
	Post-conditions: all items are removed. Contacts are not deleted.
*/
void HashTable::clear() {
	for (int i = 0; i < size; i++)
		data[i].clear();
}
