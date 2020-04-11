#ifndef LOGIN
#define LOGIN

#include<stdio.h>

// Declare struct
typedef struct {
	char username[15];
	char password[8];
	struct node* NEXT;
}Login;

// Initialise functions
void initLogin();
void login(Login* top);

#endif