#include "Database.h"
#include "Login.h"

void showMenu(struct node* top, struct node** top2);

void main()
{
	struct node* headPtr = NULL;

	//initLogin();

	init(&headPtr);
	fillDatabase(headPtr);
	
	showMenu(headPtr, &headPtr);
	
}

void showMenu(struct node* top, struct node** top2)
{
	int mode;

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

		switch (mode) {
		case 1:
			if (top == NULL) {
				addItemAtStart(&top2);
			}
			else {
				addItemAtEnd(top);
			}
			break;
		case 2:
			if (top == NULL) {
				printf("\nDatabase is empty, can't display!");
			}
			else {
				displayDatabase(top);
			}
			break;
		case 3:
			if (top == NULL) {
				printf("\nDatabase is empty, can't display!");
			}
			else {
				displayItem(top);
			}
			break;
		case 4:
			if (top == NULL) {
				printf("\nDatabase is empty, can't update stock items!");
			}
			else {
				updateItem(top);
			}
			break;
		case 5:
			if (top == NULL) {
				printf("Database is empty, can't remove stock items!");
			}
			else {
				deleteItem(top, &top2);
			}
			break;
		case 6:
			if (top == NULL) {
				printf("\nDatabase is empty, unable to generate statistics!");
			}
			else {
				generateStats(top);
			}
			break;
		case 7:
			if (top == NULL) {
				printf("\nDatabase is empty, unable to create report!");
			}
			else {
				printToFile(top);
			}
			break;
		case 8:
			if (top == NULL) {
				printf("\nDatabase is empty!");
			}
			else {
				stockInOrder(top);
			}
			break;
		case -1:
			if (top == NULL) {
				printf("\nDatabase is empty!");
			}
			else {
				saveDatabase(top);
			}
			printf("\nGoodbye.");
			break;
		default:
			printf("\nInvalid Mode, please try again!");
			break;
		}
	} while (mode != -1);
	getch();
}