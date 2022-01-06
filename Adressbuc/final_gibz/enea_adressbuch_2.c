#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CONTACTS 420

typedef struct {
  int day;
  int month;
  int year;
} Date;

typedef struct {
  char street[30];
  char house_num[10];
  char postcode[12];
  char place[50];
  char country[30];
} Address;

typedef struct {
  char prefix[4];
  char number[10];
} Phonenumber;

typedef struct {
  char name[20];
  char surname[30];
  Date birthdate;
  Address address;
  Phonenumber telnr;
  char email[50];
} Contact;

typedef enum {
  Print=1,
  Add=2,
  Search=3,
  Exit=0
} OptionType;

void PrintContact(Contact c) {
    printf("Vorname:\t%s\nNachname:\t%s\nGeburtstag:\t%02d.%02d.%4d\nAddress:\t%s %s, %s %s %s\nTelnr:\t\t%s\t%s\nEmail:\t\t%s\n\n", c.name, c.surname, c.birthdate.day, c.birthdate.month, c.birthdate.year, c.address.street, c.address.house_num, c.address.postcode, c.address.place, c.address.country, c.telnr.prefix, c.telnr.number, c.email);
}

void PrintAdressbuch(Contact book[], int numEntries) {
	printf("--- Advanced Contacts | %d contact%s ---\n", numEntries, (numEntries > 1 ? "s" : ""));
	for (int i = 0; i < numEntries; i++) {
		PrintContact(book[i]);
	}
	return;
}

int AddNewEntry(Contact book[], int maxlen, int* pNumEntries, Contact newContact) {
	if (*pNumEntries < maxlen) {	
		book[(*pNumEntries)++] = newContact;	
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

Contact AddContactMenu() {
  Contact new_c;
  printf("Enter your Name: ");
  scanf("%s", new_c.name);

  printf("Enter your Surname: ");
  scanf("%s", new_c.surname);

  printf("Enter your birthdate (dd.mm.yyyy): ");
  scanf("%2d.%2d.%4d", &new_c.birthdate.day,
       &new_c.birthdate.month, &new_c.birthdate.year);

  printf("Enter your Street: ");
  scanf("%s", new_c.address.street);

  printf("Enter your Housenumber: ");
  scanf("%s", new_c.address.house_num);

  printf("Enter your Postcode: ");
  scanf("%s", new_c.address.postcode);

  printf("Enter your City: ");
  scanf("%s", new_c.address.place);

  printf("Enter your Country: ");
  scanf("%s", new_c.address.country);

  printf("Enter your Phonenumber: ");
  scanf("%3s %7s", new_c.telnr.prefix, new_c.telnr.number);

  printf("Enter your Email: ");
  scanf("%s", new_c.email);

  return new_c;
}

void printMenu() {
  printf("Options:\nPrint\t\t1\nAdd\t\t2\nSearch\t\t3\nExit\t\t0\n");
}

int main()
{
    Contact book[MAX_CONTACTS]; 
    int numberOfContacts = 0;
    
    OptionType option = Print;

    Contact test = { 
      "Hans",
      "Muster",
      {
        01,
        01,
        1999
      },
      {
        "Musterstrasse",
        "1A",
        "0000",
        "Musterstadt",
        "Schweiz"
      },
      {
        "+41",
        "1234567"
      },
      "hans.muster@musterfirma.ch"
    };

    if (AddNewEntry(book, MAX_CONTACTS, &numberOfContacts, test) != EXIT_SUCCESS) {
          	printf("Error adding Entry");
          };

    while (option != 0){
      printMenu();
      printf("Enter an option from above: ");
      scanf("%i", &option);
      printf("\n");

      switch ((int)option) {
        case Print:
         PrintAdressbuch(book, numberOfContacts);
        break;
        case Add:
          Contact new_c = AddContactMenu();
          if (AddNewEntry(book, MAX_CONTACTS, &numberOfContacts, new_c) != EXIT_SUCCESS) {
          	printf("Error adding Entry");
          };
        break;
        case Search:
          //find_contact();
        break;
        default:
          option = 0;
        break;
      }
    }
}
