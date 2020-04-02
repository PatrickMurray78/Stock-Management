#include<stdio.h>
#include<conio.h>
#include<string.h>

#include "Database.h"

void main()
{
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
	} while (mode != -1);

	_getch();
}