#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sqlite3.h>

typedef struct {
	int number;
	char name[20];
} menuitem;

typedef struct {
	char name[20];
	char addr[50];
	char phone[10];
} contact;

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
			    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"\
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

void insert_records(sqlite3 *db, char *zErrMsg, contact cnt) {	
	int rc;
	char *insert_init;
	sqlite3_stmt *stmt;
	insert_init = "INSERT INTO CONTACTS (NAME,ADDRESS,PHONENUMBER) " \
		       "VALUES (?, ?, ?);";

	rc = sqlite3_prepare_v2(db, insert_init, -1, &stmt, NULL);

	if ( rc != SQLITE_OK ){
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	sqlite3_bind_text(stmt, 1, cnt.name, 20, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, cnt.addr, 50, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, cnt.phone, 10, SQLITE_TRANSIENT);
	
	for (;;) {
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_ROW)
			break;	
	}

	if ( rc != SQLITE_DONE ) {
		fprintf(stderr, "SQL Execution failed: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return;
	}

	sqlite3_finalize(stmt);
	return;
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


void delete_record(sqlite3 *db, char *zErrMsg, int name) {
	int rc;
	sqlite3_stmt *del_record;

	rc = sqlite3_prepare_v2(db, "DELETE FROM CONTACTS WHERE ID = ?;", -1, &del_record, NULL);
	if ( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL Error Prepare failed: %s\n", sqlite3_errmsg(db));
		return;
	}
	sqlite3_bind_int(del_record, 1, name);

	for (;;) {
		rc = sqlite3_step(del_record);
		if (rc != SQLITE_ROW)
			break;	
	}

	if ( rc != SQLITE_DONE ) {
		fprintf(stderr, "SQL Execution failed: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(del_record);
		return;
	}

	sqlite3_finalize(del_record);
	return;
}

void find_record(sqlite3 *db, char *zErrMsg, char *query) {
	int rc;
	sqlite3_stmt *find_record;

	rc = sqlite3_prepare_v2(db, "SELECT * FROM CONTACTS WHERE NAME = ?;", -1, &find_record, NULL);
	if ( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL Error Prepare failed: %s\n", sqlite3_errmsg(db));
		return;
	}
	sqlite3_bind_text(find_record, 1, query, strlen(query), SQLITE_TRANSIENT);

	for (;;) {
		rc = sqlite3_step(find_record);
		if (rc != SQLITE_ROW)
			break;
		
		int id = sqlite3_column_int (find_record, 0);
		const char *name = sqlite3_column_text(find_record, 1);
		const char *address = sqlite3_column_text(find_record, 2);
		const char *phonenumber = sqlite3_column_text(find_record, 3);
		if (name == NULL)
			name = "(NULL)";
		if (address == NULL)
			address = "(NULL)";
		if (phonenumber == NULL)
			phonenumber = "(NULL)";
		printf("\nID = %d\nNAME = %s\nADDRESS = %s\nPHONENUMBER = %s\n\n", id, name, address, phonenumber);
	}

	if ( rc != SQLITE_DONE ) {
		fprintf(stderr, "SQL Execution failed: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(find_record);
		return;
	}

	sqlite3_finalize(find_record);
	return;
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
			case 3:
				int name_id;
				printf("Enter the ID of contact to delete: ");
				scanf("%d", &name_id);
				delete_record(db, zErrMsg, name_id);
				select_all_records(db, zErrMsg);
				break;
			case 4:
				contact new_c;
				printf("Enter the NAME of the new contact: ");
				scanf("%s", &new_c.name);
				printf("Enter the ADDRESS of the new contact: ");
				scanf("%s", &new_c.addr);
				printf("Enter the PHONENUMBER of the new contact: ");
				scanf("%s", &new_c.phone);
				insert_records(db, zErrMsg, new_c);
				select_all_records(db, zErrMsg);
				break;
			default :
				printf("Exiting ...\n");
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

		contact c = {
			"3n3a",
			"Street 1",
			"0791234567",
		};
		insert_records(db, zErrMsg, c);
	}

	menu(db, zErrMsg);

	sqlite3_close(db);
	return 0;
}
