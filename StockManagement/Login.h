#ifndef LOGIN
#define LOGIN

#include<stdio.h>

typedef struct {
	char username[15];
	char password[8];
	struct node* NEXT;
}Login;

void initLogin();
void login(Login* top);

#endif