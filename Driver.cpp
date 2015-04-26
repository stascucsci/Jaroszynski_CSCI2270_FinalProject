#include "common.h"
#include "HashTable.h"
#include "HashTableItem.h"
#include "ContactBook.h"
#include "Contact.h"

int main(int argc, char **argv)
{
	ContactBook cb;
	cb.readFromFile("us-500.csv");
	cb.firstNameTable->print();
}
