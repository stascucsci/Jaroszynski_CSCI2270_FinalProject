#include "HashTableItem.h"

HashTableItem::HashTableItem(string key_, Contact *c)
{
	this->key = key_;
	if (c)
		this->values.push_back(c);
}

