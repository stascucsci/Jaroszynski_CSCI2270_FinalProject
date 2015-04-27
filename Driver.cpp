#include "common.h"
#include "HashTable.h"
#include "HashTableItem.h"
#include "ContactBook.h"
#include "Contact.h"

ContactBook *cb;

string getInput();
string getInput(string s);

void findContact();
void addContact();
void deleteContact();
void printHashTable();
void readFromFile();
void writeToFile();

int main(int argc, char **argv)
{
	cb = new ContactBook();
	bool running = 1;

	while (running) {
		cout << "======Main Menu======\n";
		cout << "1. Find contact\n";
		cout << "2. Add contact\n";
		cout << "3. Delete contact\n";
		cout << "4. Print all contacts\n";
		cout << "5. Print hash table\n";
		cout << "6. Load contacts from csv\n";
		cout << "7. Save contacts to csv\n";
		cout << "8. Quit\n";
		switch(getInput()[0]) {
			case '1':
				findContact();
				break;
			case '2':
				addContact();
				break;
			case '3':
				deleteContact();
				break;
			case '4':
				cb->printAll();
				break;
			case '5':
				printHashTable();
				break;
			case '6':
				readFromFile();
				break;
			case '7':
				writeToFile();
				break;
			case '8':
				cout << "Goodbye!\n";
				running = 0;
				break;
		}
	}
	delete cb;
	return 0;
}

void findContact()
{
	cout << "Can leave blank and it will return multiple matches if they exist\n";
	string first = getInput("First name: ");
	string last  = getInput(" Last name: ");
	string state = getInput("     State: ");
	string phone = getInput("     Phone: ");

	vector<Contact *> allFirst = cb->findAllByFirstName(first);
	vector<Contact *> allLast = cb->findAllByLastName(last);
	vector<Contact *> allState = cb->findAllByState(state);
	vector<Contact *> allPhone = cb->findAllByPhone(phone);
	vector<Contact *> ret;
	if (first.size())
		ret.insert(ret.end(), allFirst.begin(), allFirst.end());
	else if (last.size())
		ret.insert(ret.end(), allLast.begin(), allLast.end());
	else if (state.size())
		ret.insert(ret.end(), allState.begin(), allState.end());
	else if (phone.size())
		ret.insert(ret.end(), allPhone.begin(), allPhone.end());
		
	if (first.length())
		ret = cb->findMatching(ret, allFirst);
	if (last.length())
		ret = cb->findMatching(ret, allLast);
	if (state.length())
		ret = cb->findMatching(ret, allState);
	if (phone.length())
		ret = cb->findMatching(ret, allPhone);
	
	if (ret.empty()) {
		cout << "Not found\n";
	} else {
		for (int i = 0; i < ret.size(); i++)
			ret[i]->print();
	}
}

void addContact()
{
	string first = getInput("First name: ");
	string last = getInput(" Last name: ");
	string state = getInput("     State: ");
	string phone = getInput("     Phone: ");
	Contact *c = new Contact(first, last, state, phone);
	cb->addContact(c);
}

void deleteContact()
{
	cout << "Delete all that match search\n";
	string first = getInput("First name: ");
	string last  = getInput(" Last name: ");
	string state = getInput("     State: ");
	string phone = getInput("     Phone: ");

	vector<Contact *> allFirst = cb->findAllByFirstName(first);
	vector<Contact *> allLast = cb->findAllByLastName(last);
	vector<Contact *> allState = cb->findAllByState(state);
	vector<Contact *> allPhone = cb->findAllByPhone(phone);
	vector<Contact *> ret;
	if (first.size())
		ret.insert(ret.end(), allFirst.begin(), allFirst.end());
	else if (last.size())
		ret.insert(ret.end(), allLast.begin(), allLast.end());
	else if (state.size())
		ret.insert(ret.end(), allState.begin(), allState.end());
	else if (phone.size())
		ret.insert(ret.end(), allPhone.begin(), allPhone.end());
		
	if (first.length())
		ret = cb->findMatching(ret, allFirst);
	if (last.length())
		ret = cb->findMatching(ret, allLast);
	if (state.length())
		ret = cb->findMatching(ret, allState);
	if (phone.length())
		ret = cb->findMatching(ret, allPhone);

	if (ret.empty()) {
		cout << "Not found\n";
	} else {
		for (int i = 0; i < ret.size(); i++) {
			cout << "Deleted: ";
			ret[i]->print();
			cb->removeContact(ret[i]);
		}
	}
}

void printHashTable()
{
	cout << "======Which Hash Table?======\n";
	cout << "1. First names\n";
	cout << "2. Last names\n";
	cout << "3. States\n";
	cout << "4. Phone numbers\n";
	cout << "5. Cancel\n";
	string num = getInput();
	switch(num[0]) {
		case '1':
			cb->printFirstNameHashTable();
			break;
		case '2':
			cb->printLastNameHashTable();
			break;
		case '3':
			cb->printStateHashTable();
			break;
		case '4':
			cb->printPhoneHashTable();
			break;
		default:
			break;
	}
}

void readFromFile()
{
	string path = getInput("Enter path: ");
	if (cb->readFromFile(path)) {
		cout << "Error: double check path\n";
	}
}

void writeToFile()
{
	string path = getInput("Enter path: ");
	if (cb->writeToFile(path)) {
		cout << "Error writing to file\n";
	}
}

string getInput()
{
	string s;
	std::getline(std::cin, s);
	return s;
}

string getInput(string s)
{
	cout << s;
	return getInput();
}
