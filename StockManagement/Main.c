#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#include "Database.h"


void main()
{
	struct node* headPtr = NULL;
	int mode;

	initLogin();

	init(&headPtr);
	addEnd(headPtr);
	

	do
	{
		printf("\n1. Add Stock Item");
		printf("\n2. Display All Stock Items");
		printf("\n3. Display Stock Item");
		printf("\n4. Update Stock Item");
		printf("\n5. Delete Stock Item");
		printf("\n6. Generate Statistics");
		printf("\n7. Print All Stock Items To File");
		printf("\n8. List Stock Items In Order Of Monetary Value");
		printf("\nPlease enter mode: ");
		scanf("%d", &mode);

		switch (mode)
		{
			case 1:
				if (headPtr == NULL)
				{
					addItemAtStart(&headPtr);
				}
				else
				{
					addItemAtEnd(headPtr);
				}
				break;
			case 2:
				displayDatabase(headPtr);
				break;
			case 3:
				displayItem(headPtr);
				break;
			case 4:
				updateItem(headPtr);
				break;
			case 5:
				if (headPtr == NULL)
				{
					printf("Sorry the database is empty");
				}
				else
				{
					deleteItem(headPtr, &headPtr);
				}
				break;
			case 6:
				generateStats(headPtr);
				break;
			case 7:
				printToFile(headPtr);
				break;
			case 8:
				stockInOrder(headPtr);
				break;
			case -1:
				saveDatabase(headPtr);
				printf("Goodbye.");
				break;
			default:
				printf("\nInvalid Mode, please try again!");
				break;
		}

	} while (mode != -1);
	
	_getch();
}