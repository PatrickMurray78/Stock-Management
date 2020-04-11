#include "Login.h"

/*  
	This function initialises the Login Linked List.
	It does so by going through the login.txt file and 
	filling the linked list until eof encountered.
*/
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

			// The first set of credentials will be added at the start
			if (numInputs == 2 && count == 0)
			{
				count++;
				newNode->NEXT = *top;
				*top = newNode;
			}
			// The rest of the credentials get added to the end
			else if (numInputs == 2 && count != 0) {
				temp = headPtr;
				// Find the second last node
				while (temp->NEXT != NULL) {
					temp = temp->NEXT;
				}
				// Make the newNode the last node in linked list
				if (temp->NEXT == NULL) {
					newNode->NEXT = NULL;
					temp->NEXT = newNode;
				}
			}
		}
	}
	fclose(fptr);
	// Once the linked list has been filled, call login()
	login(headPtr);
}

/*
	The login function asks for a username, then searches for the
	linked list for the username, if found user is prompted to
	enter a password, if password is correct, the user is logged in.
*/
void login(Login* top)
{
	int loginSuccess = 0;
	char username[15];
	char password[20];
	int count = 0;
	int found = 0;

	Login* temp = top;

	// do/while loop until a successful login attempt is made
	do {
		printf("Username: ");
		scanf("%s", username);
		// Iterate through linked list to find username entered
		// If no username is found, ask for username again
		while (temp != NULL)
		{
			// Matching username found
			if (strcmp(temp->username, username) == 0) {
				found = 1;
				printf("Password: ");
				int i = 0;
				// Change password characters entered to "*"
				do {
					password[i] = getch();
					if (password[i] != '\r') {
						printf("*");
					}
					i++;
				} while (password[i - 1] != '\r');
				password[i - 1] = '\0';
				// Password found
				if (strcmp(temp->password, password) == 0) {
					loginSuccess = 1;
					return;
				}
				// Invalid Password
				else {
					printf("\nInvalid Password!\n\n");
				}
			}
			temp = temp->NEXT;
		}
		// If no username was found, print message
		if (found == 0)
		{
			printf("\nUsername not found, please try again!\n");
		}
		// Reset temp
		temp = top;
	} while (loginSuccess == 0);
} 