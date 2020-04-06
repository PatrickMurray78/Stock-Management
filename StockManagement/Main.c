#include "Database.h"
#include "Login.h"

void showMenu(struct node* top, struct node** top2);

void main()
{
	struct node* headPtr = NULL;

	initLogin();

	init(&headPtr);
	addEnd(headPtr);
	
	showMenu(headPtr, &headPtr);
	
}

void showMenu(struct node* top, struct node* top2)
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
			displayDatabase(top);
			break;
		case 3:
			displayItem(top);
			break;
		case 4:
			updateItem(top);
			break;
		case 5:
			if (top == NULL) {
				printf("Sorry the database is empty");
			}
			else {
				deleteItem(top, &top2);
			}
			break;
		case 6:
			generateStats(top);
			break;
		case 7:
			printToFile(top);
			break;
		case 8:
			stockInOrder(top);
			break;
		case -1:
			saveDatabase(top);
			printf("Goodbye.");
			break;
		default:
			printf("\nInvalid Mode, please try again!");
			break;
		}
	} while (mode != -1);
}