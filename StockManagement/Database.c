#include "Database.h"

/*
	This function checks the save file and if there is stock
	items in the file, it will fill the database with the first
	stock item before calling the fillDatabse() function to fill
	the rest of the database.
*/
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
		numInputs = fscanf(fptr, "%d", &newNode->number);
		numInputs += fscanf(fptr, " %[^\n]s", newNode->name);
		numInputs += fscanf(fptr, " %[^\n]s", newNode->supplierName);
		numInputs += fscanf(fptr, " %s", newNode->supplierNumber);
		numInputs += fscanf(fptr, "%d %d %f", &newNode->thresholdLimit, &newNode->numOfUnits, &newNode->costPerUnit);
		numInputs += fscanf(fptr, "%s %d %d %d %d", newNode->lastOrderDate, &newNode->isHazardousChemical,
			&newNode->department, &newNode->reOrderMonth, &newNode->authority);

		// Add to start of database
		if (numInputs == 12) {
			newNode->NEXT = *top;
			*top = newNode;
		}
	}
	fclose(fptr);
}

/*
	The fillDatabase() function is called once the first stock item
	has been added to the database from the save file. This function
	disregards the first stock item and adds the rest of the items to
	the end of the database.
*/
void fillDatabase(struct node* top)
{
	int numInputs, count = 0;
	FILE* fptr;
	fptr = fopen("database.txt", "r");

	struct node* temp = top;

	// While loop until end of the file is encountered
	while (!feof(fptr)) {
		struct node* newNode = (struct node*)malloc(sizeof(struct node));
		numInputs = fscanf(fptr, "%d", &newNode->number);
		numInputs += fscanf(fptr, " %[^\n]s", &newNode->name);
		numInputs += fscanf(fptr, " %[^\n]s", newNode->supplierName);
		numInputs += fscanf(fptr, "%s", newNode->supplierNumber);
		numInputs += fscanf(fptr, "%d %d %f", &newNode->thresholdLimit, &newNode->numOfUnits, &newNode->costPerUnit);
		numInputs += fscanf(fptr, "%s %d %d %d %d", newNode->lastOrderDate, &newNode->isHazardousChemical,
			&newNode->department, &newNode->reOrderMonth, &newNode->authority);

		// If this is the first stock item, disregard it as it is 
		// already in database
		if (numInputs == 12 && count != 0) {
			while (temp->NEXT != NULL) {
				temp = temp->NEXT;
			}

			// Add stock item to end of database
			if (temp->NEXT == NULL) {
				newNode->NEXT = NULL;
				temp->NEXT = newNode;
			}
		}
		count++;
	}
	fclose(fptr);
}

/*
	saveDatabase() is called when program is exited. It saves all contents
	of the database to a save file "database.txt"
*/
void saveDatabase(struct node* top)
{
	FILE* fptr;
	fptr = fopen("database.txt", "w");

	struct node* temp = top;

	// Iterate through database and print each item to file
	while (temp != NULL) {
		fprintf(fptr, "%d", temp->number);
		fprintf(fptr, "\n%s", temp->name);
		fprintf(fptr, "\n%s", temp->supplierName);
		fprintf(fptr, "\n%s", temp->supplierNumber);
		fprintf(fptr, "\n%d %d %.2f", temp->thresholdLimit, temp->numOfUnits, temp->costPerUnit);
		fprintf(fptr, "\n%s %d %d %d %d\n\n", temp->lastOrderDate, temp->isHazardousChemical,
			temp->department, temp->reOrderMonth, temp->authority);
		temp = temp->NEXT;
	}
	fclose(fptr);
}

/*
	This function adds a stock item to the start of the database. 
	User is prompted to enter stock details, which has input
	validation for each input.
*/
void addItemAtStart(struct node** top)
{
	// Allocate memory to newNode, which is sufficient to store stock details
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	
	// This is where user enters stock items details.
	printf("\nPlease enter the following details");
	// Stock item number is always unique when it is the first stock item
	do {
		printf("\nStock Item Number: ");
		scanf("%d", &newNode->number);
	} while (newNode->number < 0);
	do {
		printf("Stock Item Name: ");
		scanf(" %[^\n]s", newNode->name);
	} while (strlen(newNode->name) > 30);
	do {
		printf("Stock Item Supplier Name: ");
		scanf(" %[^\n]s", newNode->supplierName);
	} while (strlen(newNode->supplierNumber) > 30);
	do {
		printf("Stock Item Supplier Contact Number: ");
		scanf("%s", newNode->supplierNumber);
	} while (strlen(newNode->supplierNumber) > 10);
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
	do {
		printf("Last Order Date(DD/MM/YYYY): ");
		scanf("%s", newNode->lastOrderDate);
	} while (strlen(newNode->lastOrderDate) > 10);
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

	// Add to start
	newNode->NEXT = *top;
	*top = newNode;
}

/*
	This function adds a stock item to the end of the database.
	Stock Item Number is also validated to ensure it is unique.
*/
void addItemAtEnd(struct node* top)
{
	int stockNum;
	struct node* temp = top;
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	// This is where user enters stock items details.
	printf("\nPlease enter the following details");
	do {
		printf("\nStock Item Number: ");
		scanf("%d", &newNode->number);
		stockNum = newNode->number;
		// Validate stock number by calling isUnique()
	} while (newNode->number < 0 || isUnique(stockNum, temp) == 0);
	do {
		printf("Stock Item Name: ");
		scanf(" %[^\n]s", newNode->name);
	} while (strlen(newNode->name) > 30);
	do {
		printf("Stock Item Supplier Name: ");
		scanf(" %[^\n]s", newNode->supplierName);
	} while (strlen(newNode->supplierName) > 30);
	do {
		printf("Stock Item Supplier Contact Number: ");
		scanf("%s", newNode->supplierNumber);
	} while (strlen(newNode->supplierNumber) > 10);
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
	do {
		printf("Last Order Date(DD/MM/YYYY): ");
		scanf("%s", newNode->lastOrderDate);
	} while (strlen(newNode->lastOrderDate) > 10);
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

	// Make temp the last node
	while (temp->NEXT != NULL) {
		temp = temp->NEXT;
	}
	// Add to end
	newNode->NEXT = NULL;
	temp->NEXT = newNode;
}

/*
	isUnique() is called when checking to make sure stock item number
	is unique. It returns 1 when number is unique.
*/
int isUnique(int stockNum, struct node* top)
{
	int num = stockNum;
	struct node* temp = top;
	// Iterate through database and check if number already exists
	while (temp != NULL) {
		if (stockNum == temp->number) {
			// Stock number found, exit function and return 0
			printf("\nStock Number is not unique, please try again");
			return 0;
		}
		temp = temp->NEXT;
	}
	return 1;
}

/*
	This function is used to display all contents of the database to
	the user.
*/
void displayDatabase(struct node* top)
{
	char isHazardous[5];
	char department[15];
	char reOrderMonth[20];
	char authority[25];
	struct node* temp = top;

	// Iterate through database
	while (temp != NULL) {
		// createStrings() called to make the output of displayDatabase more
		// user friendly
		createStrings(temp, isHazardous, department, reOrderMonth, authority);

		printf("\nStock Item Number: %d", temp->number);
		printf("\nStock Item Name: %s", temp->name);
		printf("\nStock Item Supplier Name: %s", temp->supplierName);
		printf("\nStock Item Supplier Contact Number: %s", temp->supplierNumber);
		printf("\nRe-order threshold limit: %d", temp->thresholdLimit);
		printf("\nNumber of Units: %d", temp->numOfUnits);
		printf("\nCost per Unit: %.2f", temp->costPerUnit);
		printf("\nLast Order Date(DDMMYYYY): %s", temp->lastOrderDate);
		printf("\nDoes this item need to be stored in a hazardous chemical store?");
		printf("\n-> %s", isHazardous);
		printf("\nDepartment: %s", department);
		printf("\nRe-order Month: %s", reOrderMonth);
		printf("\nAuthority: %s\n", authority);
		temp = temp->NEXT;
	}
}

/*
	This function is used to display the details of a certain stock item, 
	which is searched by user by stock item number or stock item name.
*/
void displayItem(struct node* top)
{
	char searchName[30];
	char isHazardous[5];
	char department[15];
	char reOrderMonth[20];
	char authority[25];
	int option, searchNum, ret;
	struct node* temp = top;

	do {
		printf("\nWould you like to search by:");
		printf("\n1. Stock Item Number");
		printf("\n2. Stock Item Name");
		printf("\n=> ");
		scanf("%d", &option);
	} while (option != 1 && option != 2);

	// Search by Stock Item Number
	if (option == 1) {
		printf("\nPlease enter the Stock Item Number");
		printf("\n=> ");
		scanf("%d", &searchNum);
		while (temp != NULL) {
			if (temp->number == searchNum) {
				// Stock Item found, print stock item details and exit function
				createStrings(temp, isHazardous, department, reOrderMonth, authority);

				printf("\nStock Item Number: %d", temp->number);
				printf("\nStock Item Name: %s", temp->name);
				printf("\nStock Item Supplier Name: %s", temp->supplierName);
				printf("\nStock Item Supplier Contact Number: %s", temp->supplierNumber);
				printf("\nRe-order threshold limit: %d", temp->thresholdLimit);
				printf("\nNumber of Units: %d", temp->numOfUnits);
				printf("\nCost per Unit: %.2f", temp->costPerUnit);
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
		// Stock Item not found
		printf("\nStock Item number %d not in our database!", searchNum);
	}
	// Search by Stock Item Name
	else {
		printf("\nPlease enter the Stock Item Name");
		printf("\n=> ");
		scanf(" %[^\n]s", searchName);
		while (temp != NULL) {
			ret = strcmp(temp->name, searchName);
			if (ret == 0) {
				// Stock Item found, print stock item details and exit function
				createStrings(temp, isHazardous, department, reOrderMonth, authority);

				printf("\nStock Item Number: %d", temp->number);
				printf("\nStock Item Name: %s", temp->name);
				printf("\nStock Item Supplier Name: %s", temp->supplierName);
				printf("\nStock Item Supplier Contact Number: %s", temp->supplierNumber);
				printf("\nRe-order threshold limit: %d", temp->thresholdLimit);
				printf("\nNumber of Units: %d", temp->numOfUnits);
				printf("\nCost per Unit: %.2f", temp->costPerUnit);
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
		// Stock Item not found
		printf("\nStock Item name %s not in our database!", searchName);
	}
}

/*
	The updateItem() function searches through the database for a
	stock item number or stock item name. Once found user is prompted
	to update certain details for stock item.
*/
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
	// Search by Stock Item Number
	if (option == 1) {
		printf("\nPlease enter the Stock Item Number");
		printf("\n=> ");
		scanf("%d", &searchNum);
		while (temp != NULL) {
			// Stock Item found
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
	// Search by Stock Item Name
	else {
		printf("\nPlease enter the Stock Item Name");
		printf("\n=> ");
		scanf(" %[^\n]s", searchName);
		while (temp != NULL) {
			// Stock Item found
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

/*
	This function removes a stock item from the database, either from
	the start, from the end or from somewhere in between.
*/
void deleteItem(struct node* top, struct node** top2)
{
	int searchNum, count = 0;
	struct node* temp = top;
	struct node* prevTemp;

	do {
		printf("\nPlease enter Stock Item Number to delete: ");
		scanf("%d", &searchNum);
	} while (searchNum < 0);

	// Find Stock Item
	while (temp->NEXT != NULL && temp->number != searchNum) {
		count++;
		prevTemp = temp;
		temp = temp->NEXT;
	}
	// Delete at the start of database
	if (count == 0) {
		temp = *top2;
		*top2 = temp->NEXT;

		free(temp);
		return;
	}
	// Delete when stock item is not at the start or the end
	if (temp->number == searchNum && temp->NEXT != NULL && count != 0) {
		prevTemp->NEXT = temp->NEXT;
		free(temp);
		return;
	}
	// Delete at the end of database
	if (temp->NEXT == NULL && temp->number == searchNum) {
		prevTemp->NEXT = NULL;
		free(temp);
	}
	// Stock item not found
	else {
		printf("\nStock Item %d not found", searchNum);
	}
}

/*
	The generateStats() function calculates certain statistics from all
	the items in the database. You can choose between A, B and C and also 
	the department you wish you get the statistics for i.e Office/Maintenance.
*/
void generateStats(struct node* top)
{
	char option = ' ';
	float stockPercentage, size, count = 0;
	int department;
	struct node* temp = top;
	size = (float)length(top);

	// Menu
	do {
		printf("\nA. %% of stock items below the re-order threshold limit");
		printf("\nB. %% of stock items below twice the re-order threshold limit");
		printf("\nC. %% of stock items above twice the re-order threshold limit");
		printf("\n=> ");
		scanf(" %c", &option);
	} while (option != 'A' && option != 'B' && option != 'C');
	// Select department menu
	do {
		printf("\nPlease select a department");
		printf("\n1. Office");
		printf("\n2. Maintenance");
		printf("\n=> ");
		scanf("%d", &department);
	} while (department != 1 && department != 2);

	// A selected
	if (option == 'A') {
		// Office department selected
		if (department == 1) {
			while (temp != NULL) {
				// Increment count if conditions are met
				if (temp->department == 1) {
					if (temp->numOfUnits < temp->thresholdLimit) {
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		// Maintenance department selected
		else if (department == 2) {
			while (temp != NULL) {
				if (temp->department == 2) {
					if (temp->numOfUnits < temp->thresholdLimit) {
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		printf("\n%.2f%% of the items are below the re-order threshold limit\n", stockPercentage);
	}
	// B selected
	else if (option == 'B') {
		if (department == 1) {
			while (temp != NULL) {
				if (temp->department == 1) {
					if (temp->numOfUnits < (temp->thresholdLimit * 2)) {
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		else if (department == 2) {
			while (temp != NULL) {
				if (temp->department == 2) {
					if (temp->numOfUnits < (temp->thresholdLimit * 2)) {
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		printf("\n%.2f%% of the items are below twice the re-order threshold limit\n", stockPercentage);
	}
	// C selected
	else if (option == 'C') {
		if (department == 1) {
			while (temp != NULL) {
				if (temp->department == 1) {
					if (temp->numOfUnits > (temp->thresholdLimit * 2)) {
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		else if (department == 2) {
			while (temp != NULL) {
				if (temp->department == 2) {
					if (temp->numOfUnits > (temp->thresholdLimit * 2)) {
						count++;
					}
				}
				temp = temp->NEXT;
			}
			stockPercentage = (count / size) * 100;
		}
		printf("\n%.2f%% of the items are above twice the re-order threshold limit\n", stockPercentage);
	}
}

/*
	createReport() creates a structured report to "report.txt". It also
	calculates the statistics and prints to file.
*/
void createReport(struct node* top)
{
	float stockPercentage, size, count = 0;
	char isHazardous[5];
	char department[15];
	char reOrderMonth[20];
	char authority[25];

	size = (float)length(top);
	FILE* fptr;
	fptr = fopen("report.txt", "w");

	struct node* temp = top;

	// Iterate through database and print stock items to file
	while (temp != NULL) {
		createStrings(temp, isHazardous, department, reOrderMonth, authority);

		fprintf(fptr, "Stock Item Number: %d", temp->number);
		fprintf(fptr, "\nStock Item Name: %s", temp->name);
		fprintf(fptr, "\nStock Item Supplier Name: %s", temp->supplierName);
		fprintf(fptr, "\nStock Item Supplier Contact Number: %s", temp->supplierNumber);
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
	while (temp != NULL) {
		// Office department
		if (temp->department == 1) {
			if (temp->numOfUnits < temp->thresholdLimit) {
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\n%.2f%% of the items are below the re-order threshold limit in the Office Department", stockPercentage);
	count = 0;
	while (temp != NULL) {
		// Maintenance department
		if (temp->department == 2) {
			if (temp->numOfUnits < temp->thresholdLimit) {
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\n%.2f%% of the items are below the re-order threshold limit in the Maintenance Department", stockPercentage);
	count = 0;
	while (temp != NULL) {
		// Office department
		if (temp->department == 1) {
			if (temp->numOfUnits < (temp->thresholdLimit * 2)) {
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\n%.2f%% of the items are below twice the re-order threshold limit in the Office Department", stockPercentage);
	count = 0;
	while (temp != NULL) {
		// Maintenance department
		if (temp->department == 2) {
			if (temp->numOfUnits < (temp->thresholdLimit * 2)) {
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\n%.2f%% of the items are below twice the re-order threshold limit in the Maintenance Department", stockPercentage);
	count = 0;
	while (temp != NULL) {
		// Office department
		if (temp->department == 1) {
			if (temp->numOfUnits > (temp->thresholdLimit * 2)) {
				count++;
			}
		}
		temp = temp->NEXT;
	}
	temp = top;
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\n%.2f%% of the items are above twice the re-order threshold limit in the Office Department", stockPercentage);
	count = 0;
	while (temp != NULL) {
		// Maintenance department
		if (temp->department == 2) {
			if (temp->numOfUnits > (temp->thresholdLimit * 2)) {
				count++;
			}
		}
		temp = temp->NEXT;
	}
	stockPercentage = (count / size) * 100;
	fprintf(fptr, "\n%.2f%% of the items are above twice the re-order threshold limit in the Maintenance Department", stockPercentage);
	fclose(fptr);
}

/*
	This function sorts all the stock items in order of their monetary
	value.
*/
void stockInOrder(struct node* top)
{
	// Declare variables
	int sorted, count, highestStockNum;
	float highest, newHighest, value;
	struct node* temp = top;

	// Initialise variables
	sorted = count = highestStockNum = 0;
	highest = (float)temp->numOfUnits * temp->costPerUnit;
	newHighest = highest;
	highestStockNum = temp->number;
	for (int i = 0; i < length(top); i++) {
		count++;
		while (temp != NULL) {
			value = temp->numOfUnits * temp->costPerUnit;
			// Find the highest value
			if (value > highest && count == 1) {
				highest = value;
				newHighest = highest;
				highestStockNum = temp->number;
			}
			// Find the next highest values
			else if (value < highest && count != 1) {
				// If the newHighest is equal to the highest, make this
				// value the newHighest
				if (newHighest == highest) {
					newHighest = value;
				}
				// If the value is lower than the highest but greater than the
				// newHighest, make this value the newHighest
				if (value > newHighest && value < highest) {
					newHighest = value;
					highestStockNum = temp->number;
				}
				// If the value is equal to the newhighest but less than the highest
				// make this value the newhighest
				else if (value == newHighest && value < highest) {
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

/*
	The length() function simply calculates the length of the database by
	iterating through the databse and incrementing i;
*/
int length(struct node* top)
{
	int i = 0;
	struct node* temp = top;

	while (temp != NULL) {
		i++;
		temp = temp->NEXT;
	}
	return i;
}

/*
	This function creates strings from some of the options the user selected.
	This makes the output more user friendly and also makes the database easier 
	to work with prior to stringifying some elements in the databae.
*/
char createStrings(struct node* temp, char isHazardous[5], char department[15], char reOrderMonth[20], char authority[20])
{
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
	return isHazardous, department, reOrderMonth, authority;
}
