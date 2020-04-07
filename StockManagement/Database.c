#include "Database.h"

void init(struct node** top)
{
	int numInputs, count = 0;
	FILE* fptr;
	fptr = fopen("database.txt", "r");

	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	if (fptr == NULL) {
		printf("\nSorry the file could not be opened");
	}
	else {
		numInputs = fscanf(fptr, "%d %s", &newNode->number, &newNode->name);
		numInputs += fscanf(fptr, "%s %ld", newNode->supplierName, &newNode->supplierNumber);
		numInputs += fscanf(fptr, "%d %d %f", &newNode->thresholdLimit, &newNode->numOfUnits, &newNode->costPerUnit);
		numInputs += fscanf(fptr, "%s %d %d %d %d", newNode->lastOrderDate, &newNode->isHazardousChemical,
			&newNode->department, &newNode->reOrderMonth, &newNode->authority);

		if (numInputs == 12) {
			newNode->NEXT = *top;
			*top = newNode;
		}
	}
	fclose(fptr);
}

void fillDatabase(struct node* top)
{
	int numInputs, count = 0;
	FILE* fptr;
	fptr = fopen("database.txt", "r");

	struct node* temp = top;

	while (!feof(fptr)) {
		struct node* newNode = (struct node*)malloc(sizeof(struct node));
		numInputs = fscanf(fptr, "%d %s", &newNode->number, &newNode->name);
		numInputs += fscanf(fptr, "%s %ld", newNode->supplierName, &newNode->supplierNumber);
		numInputs += fscanf(fptr, "%d %d %f", &newNode->thresholdLimit, &newNode->numOfUnits, &newNode->costPerUnit);
		numInputs += fscanf(fptr, "%s %d %d %d %d", newNode->lastOrderDate, &newNode->isHazardousChemical,
			&newNode->department, &newNode->reOrderMonth, &newNode->authority);

		if (numInputs == 12 && count != 0) {
			while (temp->NEXT != NULL) {
				temp = temp->NEXT;
			}

			if (temp->NEXT == NULL) {
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

	while (temp != NULL) {
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
	do {
		printf("\nStock Item Number: ");
		scanf("%d", &newNode->number);
	} while (newNode->number < 0);
	printf("Stock Item Name: ");
	scanf("%s", newNode->name);
	printf("Stock Item Supplier Name: ");
	scanf("%s", newNode->supplierName);
	do {
		printf("Stock Item Supplier Contact Number: ");
		scanf("%d", &newNode->supplierNumber);
	} while (newNode->supplierNumber < 0);
	do {
		printf("Re-order threshold limit: ");
		scanf("%d", &newNode->thresholdLimit);
	} while (newNode->thresholdLimit < 0);
	do {
		printf("Number of Units: ");
		scanf("%d", &newNode->numOfUnits);
	} while (newNode->numOfUnits < 0);
	do {
		printf("Cost per Unit: ");
		scanf("%f", &newNode->costPerUnit);
	} while (newNode->costPerUnit < 0);
	printf("Last Order Date(DD/MM/YYYY): ");
	scanf("%s", newNode->lastOrderDate);
	do {
		printf("Does this item need to be stored in a hazardous chemical store?");
		printf("\n1. Yes");
		printf("\n2. No");
		printf("\n=> ");
		scanf("%d", &newNode->isHazardousChemical);
	} while (newNode->isHazardousChemical != 1 && newNode->isHazardousChemical != 2);
	do {
		printf("Which Department does this stock item belong to?");
		printf("\n1. Office");
		printf("\n2. Maintenance");
		printf("\n=> ");
		scanf("%d", &newNode->department);
	} while (newNode->department != 1 && newNode->department != 2);
	do {
		printf("Which of the following months do items need to re-order?");
		printf("\n1. No Specified Month");
		printf("\n2. Feb");
		printf("\n3. August");
		printf("\n=> ");
		scanf("%d", &newNode->reOrderMonth);
	} while (newNode->reOrderMonth < 1 || newNode->reOrderMonth > 3);
	do {
		printf("Which of the following people need to authorise the purchase?");
		printf("\n1. Managing Director");
		printf("\n2. Financial Controller");
		printf("\n3. Department Manager");
		printf("=> ");
		scanf("%d", &newNode->authority);
	} while (newNode->authority < 1 || newNode->authority > 3);

	newNode->NEXT = *top;
	*top = newNode;
}

void addItemAtEnd(struct node* top)
{
	int stockNum;
	struct node* temp = top;
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	printf("\nPlease enter the following details");
	do {
		printf("\nStock Item Number: ");
		scanf("%d", &newNode->number);
		stockNum = newNode->number;
	} while (newNode->number < 0 || isUnique(stockNum, temp) == 0);
	printf("Stock Item Name: ");
	scanf("%s", newNode->name);
	printf("Stock Item Supplier Name: ");
	scanf("%s", newNode->supplierName);
	do {
		printf("Stock Item Supplier Contact Number: ");
		scanf("%d", &newNode->supplierNumber);
	} while (newNode->supplierNumber < 0);
	do {
		printf("Re-order threshold limit: ");
		scanf("%d", &newNode->thresholdLimit);
	} while (newNode->thresholdLimit < 0);
	do {
		printf("Number of Units: ");
		scanf("%d", &newNode->numOfUnits);
	} while (newNode->numOfUnits < 0);
	do {
		printf("Cost per Unit: ");
		scanf("%f", &newNode->costPerUnit);
	} while (newNode->costPerUnit < 0);
	printf("Last Order Date(DD/MM/YYYY): ");
	scanf("%s", newNode->lastOrderDate);
	do {
		printf("Does this item need to be stored in a hazardous chemical store?");
		printf("\n1. Yes");
		printf("\n2. No");
		printf("\n=> ");
		scanf("%d", &newNode->isHazardousChemical);
	} while (newNode->isHazardousChemical != 1 && newNode->isHazardousChemical != 2);
	do {
		printf("Which Department does this stock item belong to?");
		printf("\n1. Office");
		printf("\n2. Maintenance");
		printf("\n=> ");
		scanf("%d", &newNode->department);
	} while (newNode->department != 1 && newNode->department != 2);
	do {
		printf("Which of the following months do items need to re-order?");
		printf("\n1. No Specified Month");
		printf("\n2. Feb");
		printf("\n3. August");
		printf("\n=> ");
		scanf("%d", &newNode->reOrderMonth);
	} while (newNode->reOrderMonth < 1 || newNode->reOrderMonth > 3);
	do {
		printf("Which of the following people need to authorise the purchase?");
		printf("\n1. Managing Director");
		printf("\n2. Financial Controller");
		printf("\n3. Department Manager");
		printf("\n=> ");
		scanf("%d", &newNode->authority);
	} while (newNode->authority < 1 || newNode->authority > 3);

	while (temp->NEXT != NULL) {
		temp = temp->NEXT;
	}

	newNode->NEXT = NULL;
	temp->NEXT = newNode;
}

int isUnique(int stockNum, struct node* top)
{
	int num = stockNum;
	struct node* temp = top;
	while (temp != NULL) {
		if (stockNum == temp->number) {
			printf("\nStock Number is not unique, please try again");
			return 0;
		}
		temp = temp->NEXT;
	}
	return 1;
}

void displayDatabase(struct node* top)
{
	char isHazardous[5];
	char department[15];
	char reOrderMonth[20];
	char authority[20];
	struct node* temp = top;

	while (temp != NULL) {
		if (temp->isHazardousChemical == 1) {
			strcpy(isHazardous, "Yes");
		}
		else if (temp->isHazardousChemical == 2) {
			strcpy(isHazardous, "No");
		}

		if (temp->department == 1) {
			strcpy(department, "Office");
		}
		else if (temp->department == 2) {
			strcpy(department, "Maintenance");
		}

		if (temp->reOrderMonth == 1) {
			strcpy(reOrderMonth, "No Specified Month");
		}
		else if (temp->reOrderMonth == 2) {
			strcpy(reOrderMonth, "February");
		}
		else if (temp->reOrderMonth == 3) {
			strcpy(reOrderMonth, "August");
		}

		if (temp->authority == 1) {
			strcpy(authority, "Managing Director");
		}
		else if (temp->authority == 2) {
			strcpy(authority, "Financial Controller");
		}
		else if (temp->authority == 3) {
			strcpy(authority, "Departent Manager");
		}

		printf("\nStock Item Number: %d", temp->number);
		printf("\nStock Item Name: %s", temp->name);
		printf("\nStock Item Supplier Name: %s", temp->supplierName);
		printf("\nStock Item Supplier Contact Number: %d", temp->supplierNumber);
		printf("\nRe-order threshold limit: %d", temp->thresholdLimit);
		printf("\nNumber of Units: %d", temp->numOfUnits);
		printf("\nCost per Unit: %f", temp->costPerUnit);
		printf("\nLast Order Date(DDMMYYYY): %s", temp->lastOrderDate);
		printf("\nDoes this item need to be stored in a hazardous chemical store?");
		printf("\n-> %s", isHazardous);
		printf("\nDepartment: %s", department);
		printf("\nRe-order Month: %s", reOrderMonth);
		printf("\nAuthority: %s\n", authority);
		temp = temp->NEXT;
	}
}

void displayItem(struct node* top)
{
	char searchName[30];
	char isHazardous[5];
	char department[15];
	char reOrderMonth[20];
	char authority[20];
	int option, searchNum, ret;
	struct node* temp = top;

	do {
		printf("\nWould you like to search by:");
		printf("\n1. Stock Item Number");
		printf("\n2. Stock Item Name");
		printf("\n=> ");
		scanf("%d", &option);
	} while (option != 1 && option != 2);

	if (option == 1) {
		printf("\nPlease enter the Stock Item Number");
		printf("\n=> ");
		scanf("%d", &searchNum);
		while (temp != NULL) {
			if (temp->number == searchNum) {
				if (temp->isHazardousChemical == 1) {
					strcpy(isHazardous, "Yes");
				}
				else if (temp->isHazardousChemical == 2) {
					strcpy(isHazardous, "No");
				}

				if (temp->department == 1) {
					strcpy(department, "Office");
				}
				else if (temp->department == 2) {
					strcpy(department, "Maintenance");
				}

				if (temp->reOrderMonth == 1) {
					strcpy(reOrderMonth, "No Specified Month");
				}
				else if (temp->reOrderMonth == 2) {
					strcpy(reOrderMonth, "February");
				}
				else if (temp->reOrderMonth == 3) {
					strcpy(reOrderMonth, "August");
				}

				if (temp->authority == 1) {
					strcpy(authority, "Managing Director");
				}
				else if (temp->authority == 2) {
					strcpy(authority, "Financial Controller");
				}
				else if (temp->authority == 3) {
					strcpy(authority, "Departent Manager");
				}

				printf("\nStock Item Number: %d", temp->number);
				printf("\nStock Item Name: %s", temp->name);
				printf("\nStock Item Supplier Name: %s", temp->supplierName);
				printf("\nStock Item Supplier Contact Number: %d", temp->supplierNumber);
				printf("\nRe-order threshold limit: %d", temp->thresholdLimit);
				printf("\nNumber of Units: %d", temp->numOfUnits);
				printf("\nCost per Unit: %f", temp->costPerUnit);
				printf("\nLast Order Date(DDMMYYYY): %s", temp->lastOrderDate);
				printf("\nDoes this item need to be stored in a hazardous chemical store?");
				printf("\n-> %s", isHazardous);
				printf("\nDepartment: %s", department);
				printf("\nRe-order Month: %s", reOrderMonth);
				printf("\nAuthority: %s\n", authority);
				return;
			}
			temp = temp->NEXT;
		}
		printf("\nStock Item number %d not in our database!", searchNum);
	}
	else {
		printf("\nPlease enter the Stock Item Name");
		printf("\n=> ");
		scanf("%s", searchName);
		while (temp != NULL) {
			ret = strcmp(temp->name, searchName);
			if (ret == 0) {
				if (temp->isHazardousChemical == 1) {
					strcpy(isHazardous, "Yes");
				}
				else if (temp->isHazardousChemical == 2) {
					strcpy(isHazardous, "No");
				}

				if (temp->department == 1) {
					strcpy(department, "Office");
				}
				else if (temp->department == 2) {
					strcpy(department, "Maintenance");
				}

				if (temp->reOrderMonth == 1) {
					strcpy(reOrderMonth, "No Specified Month");
				}
				else if (temp->reOrderMonth == 2) {
					strcpy(reOrderMonth, "February");
				}
				else if (temp->reOrderMonth == 3) {
					strcpy(reOrderMonth, "August");
				}

				if (temp->authority == 1) {
					strcpy(authority, "Managing Director");
				}
				else if (temp->authority == 2) {
					strcpy(authority, "Financial Controller");
				}
				else if (temp->authority == 3) {
					strcpy(authority, "Departent Manager");
				}

				printf("\nStock Item Number: %d", temp->number);
				printf("\nStock Item Name: %s", temp->name);
				printf("\nStock Item Supplier Name: %s", temp->supplierName);
				printf("\nStock Item Supplier Contact Number: %d", temp->supplierNumber);
				printf("\nRe-order threshold limit: %d", temp->thresholdLimit);
				printf("\nNumber of Units: %d", temp->numOfUnits);
				printf("\nCost per Unit: %f", temp->costPerUnit);
				printf("\nLast Order Date(DDMMYYYY): %s", temp->lastOrderDate);
				printf("\nDoes this item need to be stored in a hazardous chemical store?");
				printf("\n-> %s", isHazardous);
				printf("\nDepartment: %s", department);
				printf("\nRe-order Month: %s", reOrderMonth);
				printf("\nAuthority: %s\n", authority);
				return;
			}
			temp = temp->NEXT;
		}
		printf("\nStock Item name %s not in our database!", searchName);
	}
}

void updateItem(struct node* top)
{
	int option, searchNum, ret, i = 0;
	char searchName[30];
	struct node* temp = top;

	do {
		printf("\nWould you like to search by:");
		printf("\n1. Stock Item Number");
		printf("\n2. Stock Item Name");
		printf("\n=> ");
		scanf("%d", &option);
	} while (option != 1 && option != 2);
	if (option == 1) {
		printf("\nPlease enter the Stock Item Number");
		printf("\n=> ");
		scanf("%d", &searchNum);
		while (temp != NULL) {
			if (temp->number == searchNum) {
				printf("\nNew Stock Item Supplier Name: ");
				scanf("%s", temp->supplierName);
				printf("New Stock Item Supplier Contact Number: ");
				scanf("%ld", &temp->supplierNumber);
				printf("New Re-order threshold limit: ");
				scanf("%d", &temp->thresholdLimit);
				return;
			}
			temp = temp->NEXT;
		}
		printf("\nStock Item number %d not in our database!", searchNum);
	}
	else {
		printf("\nPlease enter the Stock Item Name");
		printf("\n=> ");
		scanf("%s", searchName);
		while (temp != NULL) {
			ret = strcmp(temp->name, searchName);
			if (ret == 0) {
				printf("\nNew Stock Item Supplier Name: ");
				scanf("%s", temp->supplierName);
				printf("New Stock Item Supplier Contact Number: ");
				scanf("%ld", &temp->supplierNumber);
				printf("New Re-order threshold limit: ");
				scanf("%d", &temp->thresholdLimit);
				return;
			}
			temp = temp->NEXT;
		}
		printf("\nStock Item number %d not in our database!", searchNum);
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
	int department;
	struct node* temp = top;
	size = (float)length(top);

	do {
		printf("\nA. %% of stock items below the re-order threshold limit");
		printf("\nB. %% of stock items below twice the re-order threshold limit");
		printf("\nC. %% of stock items above twice the re-order threshold limit");
		printf("\n=> ");
		scanf("%c", &option);
	} while (option != 'A' && option != 'B' && option != 'C');

	if (option == 'A')
	{
		printf("\nPlease select a department");
		printf("\n1. Office");
		printf("\n2. Maintenance");
		printf("\n=> ");
		scanf("%d", &department);

		if (department == 1)
		{
			while (temp != NULL)
			{
				if (temp->department == 1)
				{
					if (temp->numOfUnits < temp->thresholdLimit)
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
					if (temp->numOfUnits < temp->thresholdLimit)
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
		printf("\n=> ");
		scanf("%d", &department);

		if (department == 1)
		{
			while (temp != NULL)
			{
				if (temp->department == 1)
				{
					if (temp->numOfUnits < (temp->thresholdLimit * 2))
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
					if (temp->numOfUnits < (temp->thresholdLimit * 2))
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
		printf("\n=> ");
		scanf("%d", &department);

		if (department == 1)
		{
			while (temp != NULL)
			{
				if (temp->department == 1)
				{
					if (temp->numOfUnits > (temp->thresholdLimit * 2))
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
					if (temp->numOfUnits > (temp->thresholdLimit * 2))
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
			if (temp->numOfUnits < temp->thresholdLimit)
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items below the re-order threshold limit in the Office Department", stockPercentage);
	count = 0;
	while (temp != NULL)
	{
		if (temp->department == 2)
		{
			if (temp->numOfUnits < temp->thresholdLimit)
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items below the re-order threshold limit in the Maintenance Department", stockPercentage);
	count = 0;
	while (temp != NULL)
	{
		if (temp->department == 1)
		{
			if (temp->numOfUnits < (temp->thresholdLimit * 2))
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items below twice the re-order threshold limit in the Office Department", stockPercentage);
	count = 0;
	while (temp != NULL)
	{
		if (temp->department == 2)
		{
			if (temp->numOfUnits < (temp->thresholdLimit * 2))
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items below twice the re-order threshold limit in the Maintenance Department", stockPercentage);
	count = 0;
	while (temp != NULL)
	{
		if (temp->department == 1)
		{
			if (temp->numOfUnits > (temp->thresholdLimit * 2))
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items above twice the re-order threshold limit in the Office Department", stockPercentage);
	count = 0;
	while (temp != NULL)
	{
		if (temp->department == 2)
		{
			if (temp->numOfUnits > (temp->thresholdLimit * 2))
			{
				count++;
			}
		}
		temp = temp->NEXT;
	}
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\nThere are %.2f%% items above twice the re-order threshold limit in the Maintenance Department", stockPercentage);
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
	newHighest = highest;
	highestStockNum = temp->number;
	for (int i = 0; i < length(top); i++)
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
