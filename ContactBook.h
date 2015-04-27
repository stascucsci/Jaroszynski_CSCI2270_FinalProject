#ifndef ContactBook_h
#define ContactBook_h

#include "common.h"

class ContactBook {
	public:
		ContactBook(int hashSize_ = 50);
		~ContactBook();

		bool				readFromFile(string path);
		bool				writeToFile(string path);

		void				addContact(Contact *c);
		void				removeContact(Contact *c);

		vector<Contact *>	findAllByFirstName(string s);
		vector<Contact *>	findAllByLastName(string s);
		vector<Contact *>	findAllByState(string s);
		vector<Contact *>	findAllByPhone(string s);

		vector<Contact *>	findMatching(vector<Contact *> a, vector<Contact *> b);

		void printAll() const;
		void printFirstNameHashTable() const;
		void printLastNameHashTable() const;
		void printStateHashTable() const;
		void printPhoneHashTable() const;

	//private:
		vector<Contact *> contacts;
		HashTable *firstNameTable;
		HashTable *lastNameTable;
		HashTable *stateTable;
		HashTable *phoneTable;
		int hashSize;

		void createHash();
};

#endif
