#include "ContactBook.h"
#include <fstream>
#include <sstream>
#include <stdarg.h>
#include "Contact.h"
#include "HashTable.h"

using std::ifstream;
using std::ofstream;

ContactBook::ContactBook(int hashSize_)
{
	this->hashSize = hashSize_;
	this->firstNameTable = new HashTable(hashSize_);
	this->lastNameTable = new HashTable(hashSize_);
	this->stateTable = new HashTable(hashSize_);
	this->phoneTable = new HashTable(hashSize_);
}

ContactBook::~ContactBook()
{
	delete firstNameTable;
	delete lastNameTable;
	delete stateTable;
	delete phoneTable;
	for (int i = 0; i < contacts.size(); i++) {
		delete contacts[i];
	}
	contacts.clear();
}

bool ContactBook::readFromFile(string path)
{
	ifstream f(path);
	string line;
	if (!f.is_open()) {
		return 1;
	}

	std::getline(f, line);
	while (std::getline(f, line)) {
		if (line[line.length()-1] == '\n')
			line = line.substr(0, line.length()-1);
		Contact *c = new Contact();
		std::stringstream ss(line);
		string token;
		std::getline(ss, token, ','); c->firstName = token;
		std::getline(ss, token, ','); c->lastName = token;
		std::getline(ss, token, ','); c->state = token;
		std::getline(ss, token, ','); c->phone = token;
		contacts.push_back(c);
	}
	f.close();

	createHash();
	return 0;
}

bool ContactBook::writeToFile(string path)
{
	ofstream f(path);
	if (!f.is_open()) {
		return 1;
	}

	f << "firstName,lastName,state,phone\n";
	for (int i = 0; i < contacts.size(); i++) {
		f << contacts[i]->firstName << ",";
		f << contacts[i]->lastName << ",";
		f << contacts[i]->state << ",";
		f << contacts[i]->phone;
		f << endl;
	}

	f.close();
	return 0;
}

void ContactBook::addContact(Contact *c) {
	contacts.push_back(c);
	firstNameTable->addItem(c->firstName, c);
	lastNameTable->addItem(c->lastName, c);
	stateTable->addItem(c->state, c);
	phoneTable->addItem(c->phone, c);
}

void ContactBook::removeContact(Contact *c) {
	for (auto i = contacts.begin(); i != contacts.end(); i++) {
		if (*i == c) {
			contacts.erase(i);
			break;
		}
	}
	firstNameTable->removeItem(c->firstName, c);
	lastNameTable->removeItem(c->lastName, c);
	stateTable->removeItem(c->state, c);
	phoneTable->removeItem(c->phone, c);
	delete c;
}

vector<Contact *> ContactBook::findAllByFirstName(string s)
{ return firstNameTable->findItem(s); }

vector<Contact *> ContactBook::findAllByLastName(string s)
{ return lastNameTable->findItem(s); }

vector<Contact *> ContactBook::findAllByState(string s)
{ return stateTable->findItem(s); }

vector<Contact *> ContactBook::findAllByPhone(string s)
{ return phoneTable->findItem(s); }

vector<Contact *> ContactBook::findMatching(vector<Contact *> a, vector<Contact *> b)
{
	vector<Contact *> ret;
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < b.size(); j++)
			if (a[i] == b[j])
				ret.push_back(a[i]);
	return ret;
}

void ContactBook::createHash()
{
	firstNameTable->clear();
	lastNameTable->clear();
	stateTable->clear();
	phoneTable->clear();
	for (int i = 0; i < contacts.size(); i++) {
		firstNameTable->addItem(contacts[i]->firstName, contacts[i]);
		lastNameTable->addItem(contacts[i]->lastName, contacts[i]);
		stateTable->addItem(contacts[i]->state, contacts[i]);
		phoneTable->addItem(contacts[i]->phone, contacts[i]);
	}
}

void ContactBook::printAll() const
{
	if (contacts.empty())
		cout << "Empty\n";
	for (int i = 0; i < contacts.size(); i++)
		contacts[i]->print();
}

void ContactBook::printFirstNameHashTable() const
{ firstNameTable->print(); }

void ContactBook::printLastNameHashTable() const
{ lastNameTable->print(); }

void ContactBook::printStateHashTable() const
{ stateTable->print(); }

void ContactBook::printPhoneHashTable() const
{ phoneTable->print(); }

