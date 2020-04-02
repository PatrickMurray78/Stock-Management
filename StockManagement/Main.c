#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#include "Database.h"

void addItemAtStart(struct node** top);

void main()
{
	struct node* headPtr = NULL;
	int mode;

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
				addItemAtStart(&headPtr);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case -1:
				printf("Goodbye.");
				break;
			default:
				printf("\nInvalid Mode, please try again!");
				break;
		}

	} while (mode != -1);
	
	_getch();
}

void addItemAtStart(struct node** top)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	printf("\nPlease enter the following details");
	printf("\nStock Item Number: ");
	scanf("%d", &newNode->number);
	printf("Stock Item Name: ");
	scanf("%s", newNode->name);
	printf("Stock Item Supplier Name: ");
	scanf("%s", newNode->supplierName);
	printf("Stock Item Supplier Contact Number: ");
	scanf("%d", &newNode->supplierNumber);
	printf("Re-order threshold limit: ");
	scanf("%d", &newNode->thresholdLimit);
	printf("Number of Units: ");
	scanf("%d", &newNode->numOfUnits);
	printf("Cost per Unit: ");
	scanf("%f", &newNode->costPerUnit);
	printf("Last Order Date(DDMMYYYY): ");
	scanf("%d", &newNode->lastOrderDate);
	printf("Does this item need to be stored in a hazardous chemical store?");
	printf("\n1. Yes");
	printf("\n2. No");
	printf("\n=> ");
	scanf("%d", &newNode->isHazardousChemical);
	printf("Which Department does this stock item belong to?");
	printf("\n1. Office");
	printf("\n2. Maintenance");
	printf("\n=> ");
	scanf("%d", &newNode->department);
	printf("Which of the following months do items need to re-order?");
	printf("\n1. No Specified Month");
	printf("\n2. Feb");
	printf("\n3. August");
	printf("\n=> ");
	scanf("%d", &newNode->reOrderMonth);
	printf("Which of the following people need to authorise the purchase?");
	printf("\n1. Managing Director");
	printf("\n2. Financial Controller");
	printf("\n3. Department Manager");
	printf("=> ");
	scanf("%d", &newNode->authority);

	newNode->NEXT = *top;
	*top = newNode;
}