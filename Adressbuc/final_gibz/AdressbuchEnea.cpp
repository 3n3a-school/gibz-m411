#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CONTACTS 420

typedef struct
{
	int day;
	int month;
	int year;
} Date;

typedef struct
{
	char street[30];
	char house_num[10];
	char postcode[12];
	char place[50];
	char country[30];
} Address;

typedef struct
{
	char prefix[4];
	char number[10];
} Phonenumber;

typedef struct
{
	char name[20];
	char surname[30];
	Date birthdate;
	Address address;
	Phonenumber telnr;
	char email[50];
} Contact;

typedef enum
{
	Print = 1,
	Add = 2,
	Search = 3,
	Exit = 0
} OptionType;

void clearScreen() { printf("\r"); }

void PrintContact(Contact c)
{
	printf("Vorname:\t%s\nNachname:\t%s\nGeburtstag:\t%02d.%02d.%4d\nAddress:\t%s %s, %s %s %s\nTelnr:\t\t%s\t%s\nEmail:\t\t%s\n\n", c.name, c.surname, c.birthdate.day, c.birthdate.month, c.birthdate.year, c.address.street, c.address.house_num, c.address.postcode, c.address.place, c.address.country, c.telnr.prefix, c.telnr.number, c.email);
}

void PrintAdressbuch(Contact book[], int numEntries)
{
	printf("--- Advanced Contacts | %d contact%s ---\n", numEntries, (numEntries > 1 ? "s" : ""));
	for (int i = 0; i < numEntries; i++)
	{
		PrintContact(book[i]);
	}
	return;
}

int AddNewEntry(Contact book[], int maxlen, int* pNumEntries, Contact newContact)
{
	if (*pNumEntries < maxlen)
	{
		book[(*pNumEntries)++] = newContact;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

Contact AddContactMenu()
{
	Contact new_c;
	printf("Enter your Name: ");
	scanf_s("%s", new_c.name, sizeof(new_c.name));

	printf("Enter your Surname: ");
	scanf_s("%s", new_c.surname, sizeof(new_c.surname));

	printf("Enter your birthdate (dd.mm.yyyy): ");
	scanf_s("%2d.%2d.%4d", &new_c.birthdate.day,
		&new_c.birthdate.month, &new_c.birthdate.year);

	printf("Enter your Street: ");
	scanf_s("%s", new_c.address.street, sizeof(new_c.address.street));

	printf("Enter your Housenumber: ");
	scanf_s("%s", new_c.address.house_num, sizeof(new_c.address.house_num));

	printf("Enter your Postcode: ");
	scanf_s("%s", new_c.address.postcode, sizeof(new_c.address.postcode));

	printf("Enter your City: ");
	scanf_s("%s", new_c.address.place, sizeof(new_c.address.place));

	printf("Enter your Country: ");
	scanf_s("%s", new_c.address.country, sizeof(new_c.address.country));

	printf("Enter your Phone Prefix: ");
	scanf_s("%3s", new_c.telnr.prefix, sizeof(new_c.telnr.prefix));

	printf("Enter your Phonenumber: ");
	scanf_s("%7s", new_c.telnr.number, sizeof(new_c.telnr.number));

	printf("Enter your Email: ");
	scanf_s("%s", new_c.email, sizeof(new_c.email));

	return new_c;
}

Contact* SearchContact(char name[], char surname[], Contact book[], int numEntries)
{
	Contact* foundContact = NULL;
	int element = 0;

	while (foundContact == NULL && element <= numEntries - 1)
	{
		if (
			(strcmp(name, book[element].name) == 0) &&
			(strcmp(surname, book[element].surname) == 0))
		{
			foundContact = &book[element];
		}

		element++;
	}

	return foundContact;
};

void printMenu()
{
	printf("Options:\nPrint\t\t1\nAdd\t\t2\nSearch\t\t3\nExit\t\t0\n");
}

void searchMenu(Contact book[], int numberOfContacts) {
	Contact* foundC;
	char search_name[20], search_surname[20];
	printf("Enter the Name: ");
	scanf_s("%s", search_name, sizeof(search_name));
	printf("Enter the Surname: ");
	scanf_s("%s", search_surname, sizeof(search_surname));
	printf("\n");
	foundC = SearchContact(search_name, search_surname, book, numberOfContacts);
	if (foundC == NULL)
	{
		printf("\n--- Contact not found ---\n\n");
	}
	else
	{
		printf("--- Found Contact ---\n");
		PrintContact(*foundC);
	}
}

int main()
{
	Contact book[MAX_CONTACTS];
	int numberOfContacts = 0;

	OptionType option = Print;

	Contact test = {
		"Hans",
		"Muster",
		{01,
		 01,
		 1999},
		{"Musterstrasse",
		 "1A",
		 "0000",
		 "Musterstadt",
		 "Schweiz"},
		{"+41",
		 "1234567"},
		"hans.muster@musterfirma.ch" };

	if (AddNewEntry(book, MAX_CONTACTS, &numberOfContacts, test) != EXIT_SUCCESS)
	{
		printf("Error adding Entry");
	};

	
	while (option != 0)
	{	
		printMenu();
		printf("Enter an option from above: ");
		scanf_s("%i", &option);
		printf("\n");

		clearScreen();
		switch ((int)option)
		{
		case Print:
			PrintAdressbuch(book, numberOfContacts);
			break;
		case Add:
			Contact new_c = AddContactMenu();
			if (AddNewEntry(book, MAX_CONTACTS, &numberOfContacts, new_c) != EXIT_SUCCESS)
			{
				printf("Error adding Entry");
			};
			break;
		case Search:
			searchMenu(book, numberOfContacts);
			break;
		default:
			option = Exit;
			break;
		}
	}
}
