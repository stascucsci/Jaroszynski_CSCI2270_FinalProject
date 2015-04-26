#include "common.h"
#include "HashTable.h"
#include "HashTableItem.h"
#include "ContactBook.h"
#include "Contact.h"

ContactBook *cb;

string getInput();
string getInput(string s);

void findByFirst();
void findByLast();

int main(int argc, char **argv)
{
	cb = new ContactBook();
	cb->readFromFile("us-500.csv");
	bool running = 1;

	while (running) {
		cout << "======Main Menu======\n";
		cout << "1. Find by first name\n";
		cout << "2. Find by last name\n";
		cout << "3. Find movie\n";
		cout << "4. Print table contents\n";
		cout << "5. Quit\n";
		switch(getInput()[0]) {
			case '1':
				findByFirst();
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':
				cout << "Goodbye!\n";
				running = 0;
				break;
			case '6':
				break;
		}
	}
	delete cb;
	return 0;
}

void findByFirst()
{
	string name = getInput("Enter first name:\n");
	vector<Contact *> c = cb->findAllByFirstName(name);
	if (c.empty()) {
		cout << "Not found\n";
	} else {
		for (int i = 0; i < c.size(); i++) {
			c[i]->print();
		}
	}
}

void findByLast()
{
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
