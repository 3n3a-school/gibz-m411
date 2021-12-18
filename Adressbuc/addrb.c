#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sqlite3.h>

typedef struct {
	int number;
	char name[20];
} menuitem;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for(i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int file_exists(const char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else  
        return 0;
}

void create_tables(sqlite3 *db, char *zErrMsg) {	
	int rc;
	char *sql_create_table;
	sql_create_table = "CREATE TABLE CONTACTS(" \
			    "ID INT PRIMARY KEY	NOT NULL,"\
			    "NAME	TEXT	NOT NULL,"\
			    "ADDRESS	CHAR(50),"\
			    "PHONENUMBER CHAR(10));";
	rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);

	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Contacts Table created successfully\n");
	}
}

void insert_records(sqlite3 *db, char *zErrMsg) {	
	int rc;
	char *insert_init;
	insert_init = "INSERT INTO CONTACTS (ID,NAME,ADDRESS,PHONENUMBER) " \
		       "VALUES (1, '3n3a', 'Street 1', '0791234567');";

	rc = sqlite3_exec(db, insert_init, callback, 0, &zErrMsg);

	if ( rc != SQLITE_OK ){
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Record inserted with success!\n");
	}
}

void select_all_records(sqlite3 *db, char *zErrMsg) {	
	int rc;
	char *select_all_records;
	select_all_records = "SELECT * FROM CONTACTS; ";
	rc = sqlite3_exec(db, select_all_records, callback, 0, &zErrMsg);

	if ( rc != SQLITE_OK ){
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Records retrieved with success!\n");
	}
}

void find_record(sqlite3 *db, char *zErrMsg, char *query) {
	int rc;
	sqlite3_stmt *find_record;

	sqlite3_prepare_v2(db, "SELECT * FROM CONTACTS WHERE NAME LIKE '?%';", 200, &find_record, NULL);
	if ( find_record != NULL ) {
		sqlite3_bind_text(find_record, 1, query, -1, NULL);
		int step = sqlite3_step(find_record);

		if (step == SQLITE_ROW) {
			printf("ID = %d\nNAME = %s\nADDRESS = %s\nPHONENUMBER = %s\n", sqlite3_column_int(find_record, 0), sqlite3_column_text(find_record, 1), sqlite3_column_text(find_record, 2), sqlite3_column_text(find_record, 3));
		}

		rc = sqlite3_finalize(find_record);
	}

	if ( rc != SQLITE_OK ){
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Record retrieved with success.\n");
	}
}

void menu(sqlite3 *db, char *zErrMsg) {
	menuitem menu[] = {
		{0, "Exit"},
		{1, "Print All"},
		{2, "Search Contacts"},
		{3, "Delete Contact"},
		{4, "Add Contact"}
	};
	while (1 == 1) {
		int menu_number;
		for(int i=0;i < (sizeof(menu)/sizeof(*menu));i++) {
			printf("%d: %s\n", menu[i].number, menu[i].name);
		}
		printf("Enter the Menu number: ");
		scanf("%d", &menu_number);
		printf("\n");

		switch(menu_number) {
			case 1:
				select_all_records(db, zErrMsg);
				printf("\r");
				break;
			case 2:
				char name[50];
				printf("Enter the the name/part of name: ");
				scanf("%s", &name);
				find_record(db, zErrMsg, name); 
				break;
			default :
				printf("Exiting ...");
				return;
				break;
		}
	}
}

int main(int argc, char* argv[]) {	
	char db_name[] = "contacts.sqlite3";
	int db_existed = file_exists(db_name);
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open(db_name, &db);

	if( rc ) {
		fprintf(stderr, "Unable to open sqlite3 database: %s\n", sqlite3_errmsg(db));
		return(0);
	} else {
		fprintf(stderr, "Successfully opened sqlite3 database.\n");
	}

	if ( !db_existed ) {	
		create_tables(db, zErrMsg);
		insert_records(db, zErrMsg);
	}

	menu(db, zErrMsg);

	sqlite3_close(db);
	return 0;
}
