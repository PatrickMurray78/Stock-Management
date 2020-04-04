#pragma once

typedef struct node {
	int number;
	char name[20];
	char supplierName[20];
	long supplierNumber;
	int thresholdLimit;
	int numOfUnits;
	float costPerUnit;
	char lastOrderDate[10];
	int isHazardousChemical;
	int department;
	int reOrderMonth;
	int authority;
	struct node* PREV;
	struct node* NEXT;
}database;
