#include "ContactBook.h"
#include <fstream>
#include <sstream>
#include <stdarg.h>
#include "Contact.h"
#include "HashTable.h"

using std::ifstream;
using std::ofstream;

/*
	Function prototype:
	ContactBook::ContactBook(int);

	Function description:
	Constructor that initialized hash tables for each searchable parameter with the size hashSize_

	Example:
	ContactBook cb(50);

	Pre-conditions: hashSize_ != zero and should be a reasonable size depending on the data set.
	Post-conditions: new ContactBook with empty vectors and hashtables
*/
ContactBook::ContactBook(int hashSize_)
{
	this->hashSize = hashSize_;
	this->firstNameTable = new HashTable(hashSize_);
	this->lastNameTable = new HashTable(hashSize_);
	this->stateTable = new HashTable(hashSize_);
	this->phoneTable = new HashTable(hashSize_);
}

/*
	Function prototype:
	ContactBook::~ContactBook();

	Function description:
	Destructor. Deletes all hash tables and also deletes all pointers to contacts.

	Example:
	None

	Pre-conditions: None
	Post-conditions: All pointers deallocated.
*/
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

/*
	Function prototype:
	bool ContactBook::readFromFile(string);

	Function description:
	Fills the current contact book with data from a .csv file.

	Example:
	ContactBook cb;
	cb.readFromFile("data.csv");

	Pre-conditions: data file is .csv and has data in the following format:
	first,last,state,phone
	The first line contains titles which are ignored.
	Post-conditions: data from the .csv file is appended to the current data (not overwritten) and the hash tables are computed once at the end.
	Returns 0 if successful or 1 if not.
*/
bool ContactBook::readFromFile(string path)
{
	ifstream f(path);
	string line;
	if (!f.is_open()) {
		return 1;
	}

	std::getline(f, line); // Skips first line
	while (std::getline(f, line)) {
		if (line[line.length()-1] == '\n')
			line = line.substr(0, line.length()-1);
		Contact *c = new Contact();
		std::stringstream ss(line);
		string token;
		// Splits up to comma and adds to appropiate field.
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

/*
	Function prototype:
	bool ContactBook::writeToFile(string);

	Function description:
	Writes the current data to a .csv file.

	Example:
	ContactBook cb;
	cb.readFromFile("data.csv");
	cb.addContact(new Contact);
	cb.writeToFile("data.csv");

	Pre-conditions: must have write permissions at path
	Post-conditions: Contents will be saved in the .csv file at path
	Returns 0 if successful and 1 if not.
*/
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

/*
	Function prototype:
	void ContactBook::addContact(Contact *);

	Function description:
	Adds the given contact to the contact book.

	Example:
	ContactBook cb;
	cb.addContact(new Contact);

	Pre-conditions: c must be non-null. 
	Post-conditions: c is added to the vector of contacts and it is added to all of the hash tables.
*/
void ContactBook::addContact(Contact *c) {
	contacts.push_back(c);
	firstNameTable->addItem(c->firstName, c);
	lastNameTable->addItem(c->lastName, c);
	stateTable->addItem(c->state, c);
	phoneTable->addItem(c->phone, c);
}

/*
	Function prototype:
	void ContactBook::removeContact(Contact *);

	Function description:
	Removes the given contact to the contact book.

	Example:
	ContactBook cb;
	Contact *c = new Contact;
	cb.addContact(c);
	cb.removeContact(c);

	Pre-conditions: c must be non-null. 
	Post-conditions: c is removed from the vector of contacts and it is remove to all of the hash tables. It is then deleted.
*/
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

/*
	Function prototype:
	vector<Contact *> ContactBook::findMatching(vector<Contact *>, vector<Contact *>);

	Function description:
	Returns a new vector which contains the contacts that were present in both. Its purpose is to allow the combination of searches.

	Example:
	ContactBook cb;
	Contact *c1 = new Contact;
	Contact *c2 = new Contact;
	Contact *c3 = new Contact;

	vector<Contact *> a = {c1,c3};
	vector<Contact *> b = {c2,c3};

	vector<Contact *> ab = cb->findMatching(a, b);
	// ab now equals {c3}

	Pre-conditions: None
	Post-conditions: vectors a and b are not modified. returned vector contains pointers to the contacts that were in both a and b
*/
vector<Contact *> ContactBook::findMatching(vector<Contact *> a, vector<Contact *> b)
{
	vector<Contact *> ret;
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < b.size(); j++)
			if (a[i] == b[j])
				ret.push_back(a[i]);
	return ret;
}

/*
	Function prototype:
	void ContactBook::createHash();

	Function description:
	Clears all the current hash tables and recaluculates them.

	Example:
	this;
	// .. modify contacts
	this->createHash();

	Pre-conditions: None.
	Post-conditions: Hash tables are calculated. If contacts are empty, the hash tables are left empty.
*/
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

