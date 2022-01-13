#include <stdio.h>

#define MAX_NUM_PERSONEN 100

//Definition der Datentyp Schulnote:
typedef struct {
	float note;
	char vorname[20];
	char name[30];
} Schulnote;




typedef enum { Exit, Print, Average, Best, Add } Options;
void PrintMenu();
Schulnote AddSchulnoteMenu();
void PrintNotenliste(Schulnote list[], unsigned int numEntries);
float CalcAverage(Schulnote list[], unsigned int numEntries);
Schulnote* FindBest(Schulnote list[], unsigned int numEntries);
int AddNewEntry(Schulnote list[], unsigned int maxlen, unsigned int* pNumEntries, Schulnote newNote);



int main()
{
	//Your Code:
	Schulnote notenliste[MAX_NUM_PERSONEN] = {
		{ 3.5, "Hans", "Muster"},
		{ 4.0, "Maria", "Carey"},
		{ 2.5, "Josef", "Odermatt"}
	};
	Options op = Print;
	unsigned int numberOfSchulnoten = 3;

	//Fügen Sie hier eine Schleife. Die Benutzereingabe und die anschliessende Switch-Anweisung 
	//sollen solange wiederholt werden bis der Benutzer Exit (0) eingibt.
	float avg;
	Schulnote *bestSchulnote = NULL;

	while (op != Exit) {
		PrintMenu();
		scanf_s("%d", &op);
		printf("\n");

		switch (op) {
		case Print:
			PrintNotenliste(notenliste, numberOfSchulnoten);
			break;
		case Average:
			avg = CalcAverage(notenliste, numberOfSchulnoten);
			if (avg != -1) {
				printf("Average Note: %.2f\n", avg);
			}
			else {
				printf("Notenliste leer.\n");
			}
			break;
		case Best:
			bestSchulnote = FindBest(notenliste, numberOfSchulnoten);
			if (bestSchulnote != NULL) {
				printf("Name: %s, Vorname: %s, Note: %f\n", (* bestSchulnote).name, (*bestSchulnote).vorname, (*bestSchulnote).note);
			}
			else {
				printf("Notenliste leer.\n");
			}
			break;
		case Add:
			if (AddNewEntry(notenliste, MAX_NUM_PERSONEN, &numberOfSchulnoten, AddSchulnoteMenu()) != 0) {
				printf("Successfully added new Schulnote\n");
			}
			else {
				printf("An error occurred while adding new Schulnote\n");
			}
			break;
		case Exit:
			printf("Exiting...\n");
			break;
		default:
			printf("Nothing selected\n");
			break;
		}
	}

	return 0;
}

void PrintMenu() {
	printf("\nOptions:\n");
	printf("Print           .........%d\n", Print);
	printf("Average         .........%d\n", Average);
	printf("Find Best       .........%d\n", Best);
	printf("Add             .........%d\n", Add);
	printf("Exit            .........%d\n", Exit);
	printf("Enter your option> ");
}

/* ------------------------------------------------------------------------
  Funktion : die Notenliste auf der Konsole ausgeben

  Kurzbeschreibung:
	Die Funktion gibt alle Einträge der Notenliste auf der Konsole aus.

  Parameter:
  NAME               Datentyp                 Bedeutung
  list               Schulnote[]              Die Notenliste
  numEntries         unsigned int             Anzahl Einträge in der Notenliste
------------------------------------------------------------------------*/
void PrintNotenliste(Schulnote list[], unsigned int numEntries) {
	printf("Alle Noten:\n");
	for (int i = 0; i < numEntries; i++) {
		printf("Name: %s, Vorname: %s, Note: %f\n", list[i].name, list[i].vorname, list[i].note);
	}

}

/* ------------------------------------------------------------------------
  Funktion : berechnet den Durchschnitt aller Noten in der Notenliste

  Kurzbeschreibung:
	Die Funktion retorniert den Durchschnitt aller Noten in der Notenliste.

  Parameter:
  NAME               Datentyp                 Bedeutung
  list               Schulnote[]              Die Notenliste
  numEntries         unsigned int             Anzahl Eintraege in der Notenliste

  Return:
  Den Durchschnitt aller Noten in der Notenliste.
  Falls die Liste leer ist, soll -1 retorniert werden.
------------------------------------------------------------------------*/
float CalcAverage(Schulnote list[], unsigned int numEntries) {
	if (list == NULL) {
		return -1;
	}

	float sum = 0;
	for (int i = 0; i < numEntries; i++)
	{
		sum += list[i].note;
	}

	float avg = sum / numEntries;
	return avg;
}

/* -------------------------------------------------------------------------------
  Funktion : Suche nach der besten Schulnote

  Kurzbeschreibung:
	Die Funktion sucht die beste Schulnote in der Notenliste.
	Es retouniert einen Zeiger auf die beste Schulnote in der Notenliste
	oder NULL falls die Notenliste leer ist.

  Parameter:
  NAME               Datentyp                 Bedeutung
  list               Schulnote[]              Die Notenliste
  numEntries         unsigned int             Anzahl Eintraege in der Notenliste

  Return:
  einen Zeiger auf die beste Schulnote in der Notenliste
  NULL falls die Notenliste leer ist.

  Bemerkung: Falls mehrere Schüler die beste Note haben, wird ein Zeiger auf
  einen davon retourniert.
------------------------------------------------------------------------*/
Schulnote* FindBest(Schulnote list[], unsigned int numEntries) {
	if (list == NULL) {
		return NULL;
	}

	int bestMark = NULL;
	for (int i = 0; i < numEntries; i++)
	{	
		if (bestMark == NULL) {
			bestMark = i;
		}
		else if (list[i].note > list[bestMark].note) {
			bestMark = i;
		}
		
	}

	return (&list[bestMark]);
}

/* ------------------------------------------------------------------------
  Funktion : fuegt einen neuen Eintrag der Notenliste hinzu.

  Kurzbeschreibung:
	Die Funktion fuegt einen neuen Eintrag der Notenliste hinzu falls
	die Notenliste noch nicht vollbelegt ist. Die Anzahl Noten in der Notenliste
	wird entsprechend um 1 inkrementiert. Es retorniert 1 (true) falls
	der neue Eintrag erfolgreich zu der Notenliste hinzugefügt
	werden kann, sonst 0 (false).

  Parameter:
  NAME               Datentyp                 Bedeutung
  list               Schulnote[]              Die Notenliste
  maxlen             unsigned int             Die maximale Anzahl von Noten, die die Notenliste aufnehmen kann
  pNumEntries        unsigned int*            Zeiger auf Anzahl Noten in der Notenliste
  newNote            Schulnote                Die neue Note, die zu der Notenliste hinzugefügt werden soll.

  Return:
  1 (true)   Falls der neue Eintrag erfolgreich zu der Notenliste hinzugefügt wurde
  0 (false)  Sonst
------------------------------------------------------------------------*/
int AddNewEntry(Schulnote list[], unsigned int maxlen, unsigned int* pNumEntries, Schulnote newNote) {
	if (*pNumEntries < maxlen) {
		list[(*pNumEntries)++] = newNote;
		return 1;
	}
	return 0;
}

Schulnote AddSchulnoteMenu() {
	Schulnote s;
	printf("Enter your Name: ");
	scanf_s("%s", s.name, sizeof(s.name));

	printf("Enter your Vorname: ");
	scanf_s("%s", s.vorname, sizeof(s.vorname));

	printf("Enter your Schulnote: ");
	scanf_s("%f", &(s.note), sizeof(s.note));
	return s;
}