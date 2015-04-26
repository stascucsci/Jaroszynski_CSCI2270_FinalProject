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
		vector<Contact *>	findAllByAge(string s);
		Contact *			findByFullName(string s);
		Contact *			findByPhone(string s);

	//private:
		vector<Contact *> contacts;
		HashTable *firstNameTable;
		HashTable *fullNameTable;
		HashTable *lastNameTable;
		int hashSize;

		void createHash();
};

#endif
