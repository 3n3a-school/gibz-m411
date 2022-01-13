#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
} Kontakt;

struct contacts {
  Kontakt contact;
  char key[20];
  struct contacts *next;
};

struct contacts *head = NULL;
struct contacts *current = NULL;

bool contactsEmpty() {
  return head == NULL;
}

void print_contact(Kontakt c) {
    printf("Vorname:\t%s\nNachname:\t%s\nGeburtstag:\t%02d.%02d.%4d\nAddress:\t%s %s, %s %s %s\nTelnr:\t\t%s\t%s\nEmail:\t\t%s\n", c.name, c.surname, c.birthdate.day, c.birthdate.month, c.birthdate.year, c.address.street, c.address.house_num, c.address.postcode, c.address.place, c.address.country, c.telnr.prefix, c.telnr.number, c.email);
}

void print_all_contacts() {
  struct contacts *ptr = head;
  
  if (!contactsEmpty()) {
    while(ptr!=NULL) {
      print_contact(ptr->contact);
      printf("\n");
      ptr = ptr->next;
    }
  } else {
    printf("No contacts in list.\n\n");
  }
}

void prepend_contact(char* key, Kontakt contact) {
  struct contacts *link  = (struct contacts*) malloc(sizeof(struct contacts));

  strncpy(link->key, key, sizeof(link->key)-1 );
  link->contact = contact;

  link->next = head;
  head = link;
}

void editField(char* dest, char* content) {
  strncpy(dest, content, sizeof(dest)-1 );
}

void add_new_contact() {
  Kontakt new_c;
  printf("Enter your Name: ");
  scanf_s("%s", new_c.name);

  printf("Enter your Surname: ");
  scanf_s("%s", new_c.surname);

  printf("Enter your birthdate (dd.mm.yyyy): ");
  scanf_s("%2d.%2d.%4d", &new_c.birthdate.day,
       &new_c.birthdate.month, &new_c.birthdate.year);

  printf("Enter your Street: ");
  scanf_s("%s", new_c.address.street);

  printf("Enter your Housenumber: ");
  scanf_s("%s", new_c.address.house_num);

  printf("Enter your Postcode: ");
  scanf_s("%s", new_c.address.postcode);

  printf("Enter your City: ");
  scanf_s("%s", new_c.address.place);

  printf("Enter your Country: ");
  scanf_s("%s", new_c.address.country);

  printf("Enter your Phonenumber: ");
  scanf_s("%3s %7s", new_c.telnr.prefix, new_c.telnr.number);

  printf("Enter your Email: ");
  scanf_s("%s", new_c.email);

  prepend_contact(new_c.name, new_c);
}

struct contacts* find(char* key) {
   struct contacts* current = head;

   if(contactsEmpty()) {
      return NULL;
   }

   while(strcmp(current->key, key) != 0) {
	      if(current->next == NULL) {
         return NULL;
      } else {
         current = current->next;
      }
   }      
	return current;
}

void find_contact() {
  printf("Enter the name of the contact: ");
  char name[20];
  scanf_s("%s", name);

  struct contacts *foundContact = find(name);

  if (foundContact != NULL) {
    print_contact(foundContact->contact);
    printf("\n");
  } else {
    printf("No contact found.\n");
  }
}


typedef enum {
  Print=1,
  Add=2,
  Search=3,
  Exit=0
} OptionType;

void printMenu() {
  printf("Options:\nPrint\t\t1\nAdd\t\t\t2\nSearch\t\t3\nExit\t\t0\n");
}

int main()
{
    OptionType option = Print;

    Kontakt test = { 
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

    prepend_contact(test.name, test);

    while (option != 0){
      printMenu();
      printf("Enter an option from above: ");
      scanf_s("%i", &option);
      printf("\n");

      switch ((int)option) {
        case 1:
         print_all_contacts();
        break;
        case 2:
          add_new_contact();
        break;
        case 3:
          find_contact();
        break;
      }
    }
}