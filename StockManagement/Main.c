#include "Database.h"
#include "Login.h"

/*
	The main function contains the menu for the program, it also
	calls the initLogin() function which is where you enter the
	username and password. The init() and fillDatabase() functions
	are used to fill the database if there are already stock items in
	the save file.
*/
void main()
{
	int mode;
	struct node* headPtr = NULL;

	initLogin();

	init(&headPtr);
	fillDatabase(headPtr);

	// Menu
	do {
		printf("\n\n1. Add Stock Item");
		printf("\n2. Display All Stock Items");
		printf("\n3. Display Stock Item");
		printf("\n4. Update Stock Item");
		printf("\n5. Delete Stock Item");
		printf("\n6. Generate Statistics");
		printf("\n7. Print All Stock Items To File");
		printf("\n8. List Stock Items In Order Of Monetary Value");
		printf("\nPlease enter mode: ");
		scanf("%d", &mode);

		// Switch with input validation. Once -1 is entered, database is
		// saved to database.txt and program exits.
		switch (mode) {
		case 1:
			// If database is empty
			if (headPtr == NULL) {
				addItemAtStart(&headPtr);
			}
			// If database is not empty
			else {
				addItemAtEnd(headPtr);
			}
			break;
		case 2:
			if (headPtr == NULL) {
				printf("\nDatabase is empty, can't display!");
			}
			else {
				displayDatabase(headPtr);
			}
			break;
		case 3:
			if (headPtr == NULL) {
				printf("\nDatabase is empty, can't display!");
			}
			else {
				displayItem(headPtr);
			}
			break;
		case 4:
			if (headPtr == NULL) {
				printf("\nDatabase is empty, can't update stock items!");
			}
			else {
				updateItem(headPtr);
			}
			break;
		case 5:
			if (headPtr == NULL) {
				printf("Database is empty, can't remove stock items!");
			}
			else {
				deleteItem(headPtr, &headPtr);
			}
			break;
		case 6:
			if (headPtr == NULL) {
				printf("\nDatabase is empty, unable to generate statistics!");
			}
			else {
				generateStats(headPtr);
			}
			break;
		case 7:
			if (headPtr == NULL) {
				printf("\nDatabase is empty, unable to create report!");
			}
			else {
				createReport(headPtr);
			}
			break;
		case 8:
			if (headPtr == NULL) {
				printf("\nDatabase is empty, unable to display");
			}
			else {
				stockInOrder(headPtr);
			}
			break;
		case -1:
			if (headPtr == NULL) {
				printf("\nDatabase is empty!");
			}
			else {
				saveDatabase(headPtr);
			}
			printf("\nGoodbye.");
			break;
		// If incorrect input is entered
		default:
			printf("\nInvalid Mode, please try again!");
			break;
		}
	} while (mode != -1);
	getch();
}
