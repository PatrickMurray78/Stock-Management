#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#include "Database.h"

void init(struct node** top);
void addEnd(struct node* top);
void saveDatabase(struct node* top);
void addItemAtStart(struct node** top);
void addItemAtEnd(struct node* top);
void displayDatabase(struct node* top);
void displayItem(struct node* top);
void updateItem(struct node* top);
void deleteItemAtStart(struct node** top);
void deleteItemAtEnd(struct node* top, struct node* prev);
void deleteItem(struct node* top);

void main()
{
	struct node* headPtr = NULL;
	int mode;

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
				else if (headPtr->NEXT == NULL)
				{
					deleteItemAtStart(&headPtr);
				}
				else
				{
					deleteItem(headPtr);
				}
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
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

void init(struct node** top)
{
	int numInputs, count = 0;
	FILE* fptr;
	fptr = fopen("database.txt", "r");

	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	if (fptr == NULL)
	{
		printf("\nSorry the file could not be opened");
	}
	else
	{
			numInputs = fscanf(fptr, "%d %s", &newNode->number, &newNode->name);
			numInputs += fscanf(fptr, "%s %ld", newNode->supplierName, &newNode->supplierNumber);
			numInputs += fscanf(fptr, "%d %d %f", &newNode->thresholdLimit, &newNode->numOfUnits, &newNode->costPerUnit);
			numInputs += fscanf(fptr, "%d %d %d %d %d", &newNode->lastOrderDate, &newNode->isHazardousChemical,
				&newNode->department, &newNode->reOrderMonth, &newNode->authority);


			if (numInputs == 12)
			{
				newNode->NEXT = *top;
				*top = newNode;
			}
	}
	fclose(fptr);
}

void addEnd(struct node* top)
{
	int numInputs, count = 0;
	FILE* fptr;
	fptr = fopen("database.txt", "r");

	struct node* temp = top;
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	if (fptr == NULL)
	{
		printf("\nSorry the file could not be opened");
	}
	else
	{
		while (!feof(fptr))
		{
		numInputs = fscanf(fptr, "%d %s", &newNode->number, &newNode->name);
		numInputs += fscanf(fptr, "%s %ld", newNode->supplierName, &newNode->supplierNumber);
		numInputs += fscanf(fptr, "%d %d %f", &newNode->thresholdLimit, &newNode->numOfUnits, &newNode->costPerUnit);
		numInputs += fscanf(fptr, "%d %d %d %d %d", &newNode->lastOrderDate, &newNode->isHazardousChemical,
			&newNode->department, &newNode->reOrderMonth, &newNode->authority);


			if (numInputs == 12 && count != 0)
			{
					while (temp->NEXT != NULL)
					{
						temp = temp->NEXT;
					}

					newNode->NEXT = NULL;
					temp->NEXT = newNode;
			}
			count++;
		}
	}
	fclose(fptr);
}

void saveDatabase(struct node* top)
{
	FILE* fptr;
	fptr = fopen("database.txt", "w");

	struct node* temp = top;

	while (temp != NULL)
	{
		fprintf(fptr, "%d %s", temp->number, temp->name);
		fprintf(fptr, "\n%s %ld", temp->supplierName, temp->supplierNumber);
		fprintf(fptr, "\n%d %d %.2f", temp->thresholdLimit, temp->numOfUnits, temp->costPerUnit);
		fprintf(fptr, "\n%d %d %d %d %d\n\n", temp->lastOrderDate, temp->isHazardousChemical,
				temp->department, temp->reOrderMonth, temp->authority);
		temp = temp->NEXT;
	}

	fclose(fptr);
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

void addItemAtEnd(struct node* top)
{
	struct node* temp = top;
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

	while (temp->NEXT != NULL)
	{
		temp = temp->NEXT;
	}

	newNode->NEXT = NULL;
	temp->NEXT = newNode;
}

void displayDatabase(struct node* top)
{
	struct node* temp = top;

	while (temp != NULL)
	{
		printf("\nStock Item Number: %d", temp->number);
		printf("\nStock Item Name: %s", temp->name);
		printf("\nStock Item Supplier Name: %s", temp->supplierName);
		printf("\nStock Item Supplier Contact Number: %d", temp->supplierNumber);
		printf("\nRe-order threshold limit: %d", temp->thresholdLimit);
		printf("\nNumber of Units: %d", temp->numOfUnits);
		printf("\nCost per Unit: %f", temp->costPerUnit);
		printf("\nLast Order Date(DDMMYYYY): %d", temp->lastOrderDate);
		printf("\nDoes this item need to be stored in a hazardous chemical store?");
		printf("\n-> %d", temp->isHazardousChemical);
		printf("\nDepartment: %d", temp->department);
		printf("\nRe-order Month: %d", temp->reOrderMonth);
		printf("\nAuthority: %d\n", temp->authority);
		temp = temp->NEXT;
	}
}

void displayItem(struct node* top)
{
	struct node* temp;
	int option, searchNum, ret;
	char searchName[30];

	temp = top;

	printf("\nWould you like to search by:");
	printf("\n1. Stock Item Number");
	printf("\n2. Stock Item Name");
	printf("\n=> ");
	scanf("%d", &option);
	if (option == 1)
	{
		printf("\nPlease enter the Stock Item Number");
		printf("\n=> ");
		scanf("%d", &searchNum);
		while (temp != NULL)
		{
			if (temp->number == searchNum)
			{
				printf("\nStock Item Number: %d", temp->number);
				printf("\nStock Item Name: %s", temp->name);
				printf("\nStock Item Supplier Name: %s", temp->supplierName);
				printf("\nStock Item Supplier Contact Number: %d", temp->supplierNumber);
				printf("\nRe-order threshold limit: %d", temp->thresholdLimit);
				printf("\nNumber of Units: %d", temp->numOfUnits);
				printf("\nCost per Unit: %f", temp->costPerUnit);
				printf("\nLast Order Date(DDMMYYYY): %d", temp->lastOrderDate);
				printf("\nDoes this item need to be stored in a hazardous chemical store?");
				printf("\n-> %d", temp->isHazardousChemical);
				printf("\nDepartment: %d", temp->department);
				printf("\nRe-order Month: %d", temp->reOrderMonth);
				printf("\nAuthority: %d\n", temp->authority);
			}

			temp = temp->NEXT;
		}

	}
	else {
		printf("\nPlease enter the Stock Item Name");
		printf("\n=> ");
		scanf("%s", searchName);
		while (temp != NULL)
		{
			ret = strcmp(temp->name, searchName);
			if (ret == 0)
			{
				printf("\nStock Item Number: %d", temp->number);
				printf("\nStock Item Name: %s", temp->name);
				printf("\nStock Item Supplier Name: %s", temp->supplierName);
				printf("\nStock Item Supplier Contact Number: %d", temp->supplierNumber);
				printf("\nRe-order threshold limit: %d", temp->thresholdLimit);
				printf("\nNumber of Units: %d", temp->numOfUnits);
				printf("\nCost per Unit: %f", temp->costPerUnit);
				printf("\nLast Order Date(DDMMYYYY): %d", temp->lastOrderDate);
				printf("\nDoes this item need to be stored in a hazardous chemical store?");
				printf("\n-> %d", temp->isHazardousChemical);
				printf("\nDepartment: %d", temp->department);
				printf("\nRe-order Month: %d", temp->reOrderMonth);
				printf("\nAuthority: %d\n", temp->authority);
			}

			temp = temp->NEXT;
		}
	}
}

void updateItem(struct node* top)
{
	struct node* temp;
	int option, searchNum, ret;
	char searchName[30];
	int i = 0;

	temp = top;

	printf("\nWould you like to search by:");
	printf("\n1. Stock Item Number");
	printf("\n2. Stock Item Name");
	printf("\n=> ");
	scanf("%d", &option);
	if (option == 1)
	{
		printf("\nPlease enter the Stock Item Number");
		printf("\n=> ");
		scanf("%d", &searchNum);
		while (temp != NULL)
		{
			if (temp->number == searchNum)
			{
				printf("\nNew Stock Item Supplier Name: ");
				scanf("%s", temp->supplierName);
				printf("New Stock Item Supplier Contact Number: ");
				scanf("%ld", &temp->supplierNumber);
				printf("New Re-order threshold limit: ");
				scanf("%d", &temp->thresholdLimit);
			}

			temp = temp->NEXT;
		}

	}
	else {
		printf("\nPlease enter the Stock Item Name");
		printf("\n=> ");
		scanf("%s", searchName);
		while (temp != NULL)
		{
			ret = strcmp(temp->name, searchName);
			if (ret == 0)
			{
				printf("\nNew Stock Item Supplier Name: ");
				scanf("%s", temp->supplierName);
				printf("New Stock Item Supplier Contact Number: ");
				scanf("%ld", &temp->supplierNumber);
				printf("New Re-order threshold limit: ");
				scanf("%d", &temp->thresholdLimit);
			}

			temp = temp->NEXT;
		}
	}
}

void deleteItemAtStart(struct node** top)
{
	int searchNum, ret;
	struct node* temp;

	printf("\nPlease enter Stock Item Number to delete: ");
	scanf("%d", &searchNum);
	ret = strcmp(temp->name, searchNum);
	if (ret == 0)
	{
		temp = *top;
		*top = temp->NEXT;

		free(temp);
	}
	else {
		printf("\nStock Item not found!");
	}
}

void deleteItemAtEnd(struct node* top, struct node* prev)
{
	struct node* temp = top;
	struct node* prevTemp = prev;

		prevTemp->NEXT = NULL;
		free(temp);
}

void deleteItem(struct node* top)
{
	int searchNum;
	struct node* temp = top;
	struct node* prevTemp;
	 
	printf("\nPlease enter Stock Item Number to delete: ");
	scanf("%d", &searchNum);
	while (temp->NEXT != NULL && temp->number != searchNum)
	{
		prevTemp = temp;
		temp = temp->NEXT;
	}
	if (temp->number && temp->NEXT != NULL)
	{
		prevTemp->NEXT = temp->NEXT;
		free(temp);
	}
	printf("\nStock Item not found!");
	deleteItemAtEnd(top, prevTemp);
}