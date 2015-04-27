#include "HashTable.h"
#include "HashTableItem.h"

HashTable::HashTable(int size_)
	: size(size_), data(new vector<HashTableItem>[size]) {}

HashTable::~HashTable()
{
	delete [] data;
}

void HashTable::addItem(string key, Contact *value)
{
	int hash = getHash(key);
	for (int i = 0; i < data[hash].size(); i++) {
		if (data[hash][i].key == key) {
			data[hash][i].values.push_back(value);
			return;
		}
	}
	data[hash].push_back(HashTableItem(key, value));
}

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

void HashTable::clear() {
	for (int i = 0; i < size; i++)
		data[i].clear();
}
