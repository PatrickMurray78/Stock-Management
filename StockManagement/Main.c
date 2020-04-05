#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#include "Database.h"

int login();
void init(struct node** top);
void addEnd(struct node* top);
void saveDatabase(struct node* top);
void addItemAtStart(struct node** top);
void addItemAtEnd(struct node* top);
void displayDatabase(struct node* top);
void displayItem(struct node* top);
void updateItem(struct node* top);
void deleteItem(struct node* top, struct node** top2);
int length(struct node* top);
void generateStats(struct node* top);
void printToFile(struct node* top);
void stockInOrder(struct node* top);

void main()
{
	struct node* headPtr = NULL;
	int mode;

	do
	{
		login();
	} while (login() == 0);

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

int login()
{
	int loginSuccess = 0;

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
			numInputs += fscanf(fptr, "%s %d %d %d %d", newNode->lastOrderDate, &newNode->isHazardousChemical,
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

	while (!feof(fptr))
	{
		struct node* newNode = (struct node*)malloc(sizeof(struct node));
		numInputs = fscanf(fptr, "%d %s", &newNode->number, &newNode->name);
		numInputs += fscanf(fptr, "%s %ld", newNode->supplierName, &newNode->supplierNumber);
		numInputs += fscanf(fptr, "%d %d %f", &newNode->thresholdLimit, &newNode->numOfUnits, &newNode->costPerUnit);
		numInputs += fscanf(fptr, "%s %d %d %d %d", newNode->lastOrderDate, &newNode->isHazardousChemical,
			&newNode->department, &newNode->reOrderMonth, &newNode->authority);

		if (numInputs == 12 && count != 0)
		{
				while (temp->NEXT != NULL)
				{
					temp = temp->NEXT;
				}

				if (temp->NEXT == NULL)
				{
					newNode->NEXT = NULL;
					temp->NEXT = newNode;
				}
		}
		count++;
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
		fprintf(fptr, "\n%s %d %d %d %d\n\n", temp->lastOrderDate, temp->isHazardousChemical,
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
	scanf("%s", newNode->lastOrderDate);
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
	scanf("%s", newNode->lastOrderDate);
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
		printf("\nLast Order Date(DDMMYYYY): %s", temp->lastOrderDate);
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
	int option, searchNum, ret, count = 0;
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
		while (temp != NULL && count < 5)
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
				printf("\nLast Order Date(DDMMYYYY): %s", temp->lastOrderDate);
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
				printf("\nLast Order Date(DDMMYYYY): %s", temp->lastOrderDate);
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

void deleteItem(struct node* top, struct node** top2)
{
	int searchNum, count = 0;
	struct node* temp = top;
	struct node* prevTemp;
	 
	printf("\nPlease enter Stock Item Number to delete: ");
	scanf("%d", &searchNum);
	while (temp->NEXT != NULL && temp->number != searchNum)
	{
		count++;
		prevTemp = temp;
		temp = temp->NEXT;
	}

	if (count == 0)
	{
		temp = *top2;
		*top2 = temp->NEXT;

		free(temp);
		return;
	}

	if (temp->number == searchNum && temp->NEXT != NULL && count != 0)
	{
		prevTemp->NEXT = temp->NEXT;
		free(temp);
		return;
	}
	if (temp->NEXT == NULL && temp->number == searchNum)
	{
		prevTemp->NEXT = NULL;
		free(temp);
	}
	else {
		printf("\nStock Item not found");
	}
	
}

int length(struct node* top)
{
	struct node* temp;
	temp = top;
	int i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->NEXT;
	}
	return i;
}

void generateStats(struct node* top)
{
	char option = ' ';
	float stockPercentage, size, count = 0;
	int department, reOrderThresholdLimit;
	struct node* temp = top;
	size = (float)length(top);

	do {
		printf("\nA. %% of stock items below the re-order threshold limit");
		printf("\nB. %% of stock items below twice the re-order threshold limit");
		printf("\nC. %% of stock items above twice the re-order threshold limit");
		printf("\n=> ");
		scanf("%c", &option);
	} while (option != 'A' && option != 'B' && option != 'C');

	if(option == 'A')
	{
		printf("\nPlease select a department");
		printf("\n1. Office");
		printf("\n2. Maintenance");
		printf("\n=> ");
		scanf("%d", &department);

		printf("\nPlease enter the re-order threshold limit: ");
		scanf("%d", &reOrderThresholdLimit);

		if (department == 1)
		{
			while (temp != NULL)
			{
				if (temp->department == 1)
				{
					if (temp->thresholdLimit < reOrderThresholdLimit)
					{
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		else if (department == 2)
		{
			while (temp != NULL)
			{
				if (temp->department == 2)
				{
					if (temp->thresholdLimit < reOrderThresholdLimit)
					{
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		printf("\nThere are %.2f%% items below the re-order threshold limit\n", stockPercentage);
	}
	else if (option == 'B')
	{
		printf("\nPlease select a department");
		printf("\n1. Office");
		printf("\n2. Maintenance");
		printf("\=> ");
		scanf("%d", &department);

		printf("Please enter the re-order threshold limit: ");
		scanf("%d", &reOrderThresholdLimit);

		if (department == 1)
		{
			while (temp != NULL)
			{
				if (temp->department == 1)
				{
					if (temp->thresholdLimit < (reOrderThresholdLimit * 2))
					{
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		else if (department == 2)
		{
			while (temp != NULL)
			{
				if (temp->department == 2)
				{
					if (temp->thresholdLimit < (reOrderThresholdLimit * 2))
					{
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		printf("\nThere are %.2f%% items below twice the re-order threshold limit\n", stockPercentage);
	}
	else if (option == 'C') {
		printf("\nPlease select a department");
		printf("\n1. Office");
		printf("\n2. Maintenance");
		printf("\=> ");
		scanf("%d", &department);

		printf("Please enter the re-order threshold limit: ");
		scanf("%d", &reOrderThresholdLimit);

		if (department == 1)
		{
			while (temp != NULL)
			{
				if (temp->department == 1)
				{
					if (temp->thresholdLimit > (reOrderThresholdLimit * 2))
					{
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		else if (department == 2)
		{
			while (temp != NULL)
			{
				if (temp->department == 2)
				{
					if (temp->thresholdLimit > (reOrderThresholdLimit * 2))
					{
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		printf("\nThere are %.2f%% items above twice the re-order threshold limit\n", stockPercentage);
	}
}

void printToFile(struct node* top)
{
	float stockPercentage, size, count = 0;
	int reOrderThresholdLimit = 1250;
	char isHazardous[5];
	char department[15];
	char reOrderMonth[20];
	char authority[20];
	
	size = (float)length(top);
	FILE* fptr;
	fptr = fopen("report.txt", "w");

	struct node* temp = top;

	while (temp != NULL)
	{
		if (temp->isHazardousChemical == 1)
		{
			strcpy(isHazardous, "Yes");
		}
		else if (temp->isHazardousChemical == 2)
		{
			strcpy(isHazardous, "No");
		}

		if (temp->department == 1)
		{
			strcpy(department, "Office");
		}
		else if (temp->department == 2)
		{
			strcpy(department, "Maintenance");
		}

		if (temp->reOrderMonth == 1)
		{
			strcpy(reOrderMonth, "No Specified Month");
		}
		else if (temp->reOrderMonth == 2)
		{
			strcpy(reOrderMonth, "February");
		}
		else if (temp->reOrderMonth == 3)
		{
			strcpy(reOrderMonth, "August");
		}

		if (temp->authority == 1)
		{
			strcpy(authority, "Managing Director");
		}
		else if (temp->authority == 2)
		{
			strcpy(authority, "Financial Controller");
		}
		else if (temp->authority == 3)
		{
			strcpy(authority, "Departent Manager");
		}

		fprintf(fptr, "Stock Item Number: %d", temp->number);
		fprintf(fptr, "\nStock Item Name: %s", temp->name);
		fprintf(fptr, "\nStock Item Supplier Name: %s", temp->supplierName);
		fprintf(fptr, "\nStock Item Supplier Contact Number: %d", temp->supplierNumber);
		fprintf(fptr, "\nRe-order threshold limit: %d", temp->thresholdLimit);
		fprintf(fptr, "\nNumber of Units: %d", temp->numOfUnits);
		fprintf(fptr, "\nCost per Unit: %.2f", temp->costPerUnit);
		fprintf(fptr, "\nLast Order Date(DDMMYYYY): %d", temp->lastOrderDate);
		fprintf(fptr, "\nDoes this item need to be stored in a hazardous chemical store?");
		fprintf(fptr, "\n-> %s", isHazardous);
		fprintf(fptr, "\nDepartment: %s", department);
		fprintf(fptr, "\nRe-order Month: %s", reOrderMonth);
		fprintf(fptr, "\nAuthority: %s\n\n", authority);
		temp = temp->NEXT;
	}
	while (temp != NULL)
	{
		if (temp->department == 1)
		{
			if (temp->thresholdLimit < reOrderThresholdLimit)
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items below the re-order threshold limit in the Office Department\n", stockPercentage);
	count = 0;
	while (temp != NULL)
	{
		if (temp->department == 2)
		{
			if (temp->thresholdLimit < reOrderThresholdLimit)
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items below the re-order threshold limit in the Maintenance Department\n", stockPercentage);
	count = 0;
	while (temp != NULL)
	{
		if (temp->department == 1)
		{
			if (temp->thresholdLimit < (reOrderThresholdLimit * 2))
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items below twice the re-order threshold limit in the Office Department\n", stockPercentage);
	count = 0;
	while (temp != NULL)
	{
		if (temp->department == 2)
		{
			if (temp->thresholdLimit < (reOrderThresholdLimit * 2))
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items below twice the re-order threshold limit in the Maintenance Department\n", stockPercentage);
	count = 0;
	while (temp != NULL)
	{
		if (temp->department == 1)
		{
			if (temp->thresholdLimit > (reOrderThresholdLimit * 2))
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items above twice the re-order threshold limit in the Office Department\n", stockPercentage);
	count = 0;
	while (temp != NULL)
	{
		if (temp->department == 2)
		{
			if (temp->thresholdLimit > (reOrderThresholdLimit * 2))
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items above twice the re-order threshold limit in the Maintenance Department\n", stockPercentage);
	count = 0;
	fclose(fptr);
}

void stockInOrder(struct node* top)
{
	int sorted = 0;
	int count = 0;
	int highestStockNum = 0;
	float highest, newHighest, value;
	struct node* temp = top;
	highest = (float)temp->numOfUnits * temp->costPerUnit;
	highestStockNum = temp->number;
	for(int i = 0; i < length(top); i++)
	{
		count++;
		while (temp != NULL)
		{
			
			value = temp->numOfUnits * temp->costPerUnit;
			if (value > highest && count == 1)
			{
				highest = value;
				newHighest = highest;
				highestStockNum = temp->number;
				
			}
			else if (value < highest && count != 1)
			{
				if (newHighest == highest)
				{
					newHighest = value;
				}
				if (value > newHighest && value < highest)
				{
					newHighest = value;
					highestStockNum = temp->number;
				}
				else if (value == newHighest && value < highest)
				{
					newHighest = value;
					highestStockNum = temp->number;
				}
			}
			temp = temp->NEXT;
		}
		highest = newHighest;
		printf("\nStock Number: %d Value: $%.2f", highestStockNum, highest);
		value = 0;
		temp = top;
	}
	printf("\n");
}
