#include "ContactBook.h"
#include <fstream>
#include <sstream>
#include "Contact.h"
#include "HashTable.h"

using std::ifstream;
using std::ofstream;

ContactBook::ContactBook(int hashSize_)
{
	this->hashSize = hashSize_;
	this->firstNameTable = new HashTable(hashSize_);
}

ContactBook::~ContactBook()
{
	delete firstNameTable;
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
		Contact *c = new Contact();
		std::stringstream ss(line);
		string token;
		std::getline(ss, token); c->firstName = token;
		std::getline(ss, token); c->lastName = token;
		std::getline(ss, token); c->address = token;
		std::getline(ss, token); c->phone = token;
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

	f << "firstName,lastName,address,phone\n";
	for (int i = 0; i < contacts.size(); i++) {
		f << contacts[i]->firstName << ",";
		f << contacts[i]->lastName << ",";
		f << contacts[i]->address << ",";
		f << contacts[i]->phone;
		f << endl;
	}

	f.close();
	return 0;
}

void ContactBook::addContact(Contact *c) {
	contacts.push_back(c);
	createHash();
}

void ContactBook::removeContact(Contact *c) {
	for (auto i = contacts.begin(); i != contacts.end(); i++) {
		if (*i == c) {
			contacts.erase(i);
			delete c;
			break;
		}
	}
}

vector<Contact *> ContactBook::findAllByFirstName(string s) {
	return firstNameTable->findItem(s);
}
vector<Contact *> ContactBook::findAllByLastName(string s) {}
vector<Contact *> ContactBook::findAllByAge(string s) {}
Contact * ContactBook::findByFullName(string s) {}
Contact * ContactBook::findByPhone(string s) {}

void ContactBook::createHash()
{
	for (int i = 0; i < contacts.size(); i++) {
		firstNameTable->addItem(contacts[i]->firstName, contacts[i]);
	}
}
