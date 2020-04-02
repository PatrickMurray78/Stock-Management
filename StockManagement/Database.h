#pragma once

typedef struct
{
	int number;
	char name[20];
	char supplierName[20];
	int supplierNumber;
	int thresholdLimit;
	int numOfUnits;
	float costPerUnit;
	char lastOrderData[20];
	char hazardousChemical[10];
	char department[10];
	char reOrderMonth[20];
	char authority[20];
}database;
