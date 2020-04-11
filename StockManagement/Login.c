#include "Login.h"

void initLogin()
{
	int numInputs, count = 0;
	Login* headPtr = NULL;
	FILE* fptr;
	fptr = fopen("login.txt", "r");

	Login** top = &headPtr;
	Login* temp;
	

	if (fptr == NULL)
	{
		printf("\nUnable to open file!");
	}
	else {
		while (!feof(fptr)) {
			Login* newNode = (Login*)malloc(sizeof(Login));
			numInputs = fscanf(fptr, "%s", newNode->username);
			numInputs += fscanf(fptr, "%s", newNode->password);

			if (numInputs == 2 && count == 0)
			{
				count++;
				newNode->NEXT = *top;
				*top = newNode;
			}
			else if (numInputs == 2 && count != 0) {
				temp = headPtr;
				while (temp->NEXT != NULL) {
					temp = temp->NEXT;
				}

				if (temp->NEXT == NULL) {
					newNode->NEXT = NULL;
					temp->NEXT = newNode;
				}
			}
		}
	}
	fclose(fptr);
	login(headPtr);
}

void login(Login* top)
{
	int loginSuccess = 0;
	char username[15];
	char password[20];
	int count = 0;
	int found = 0;

	Login* temp = top;

	do {
		printf("Username: ");
		scanf("%s", username);

		while (temp != NULL)
		{
			if (strcmp(temp->username, username) == 0) {
				found = 1;
				printf("Password: ");
				int i = 0;
				do {
					password[i] = getch();
					if (password[i] != '\r') {
						printf("*");
					}
					i++;
				} while (password[i - 1] != '\r');
				password[i - 1] = '\0';
				if (strcmp(temp->password, password) == 0) {
					loginSuccess = 1;
					return;
				}
				else {
					printf("\nInvalid Password!\n\n");
				}
			}
			temp = temp->NEXT;
		}
		if (found == 0)
		{
			printf("\nUsername not found, please try again!\n");
		}
		temp = top;
	} while (loginSuccess == 0);
} 