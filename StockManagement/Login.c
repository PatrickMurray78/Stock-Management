#include "Login.h"

void initLogin()
{
	Login credentials;
	FILE* fptr;
	fptr = fopen("login.txt", "r");

	fscanf(fptr, "%s", credentials.username);
	fscanf(fptr, "%s", credentials.password);
	fclose(fptr);
	login(credentials);
}

void login(Login credentials)
{
	int loginSuccess = 0;
	char username[15];
	char password[20];

	do {
		printf("Username: ");
		scanf("%s", username);

		if (strcmp(credentials.username, username) == 0) {
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
			if (strcmp(credentials.password, password) == 0) {
				loginSuccess = 1;
			}
			else {
				printf("\nInvalid Password!\n\n");
			}
		}
		else {
			printf("\nInvalid Username!\n\n");
		}
	} while (loginSuccess == 0);
} 