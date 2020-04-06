#ifndef LINKEDLIST
#define LINKEDLIST

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
}Database;

void init(struct node** top);
void addEnd(struct node* top);
void saveDatabase(struct node* top);
void addItemAtStart(struct node** top);
void addItemAtEnd(struct node* top);
void displayDatabase(struct node* top);
void displayItem(struct node* top);
void updateItem(struct node* top);
void deleteItem(struct node* top, struct node** top2);
int length(struct node* top);
void generateStats(struct node* top);
void printToFile(struct node* top);
void stockInOrder(struct node* top);

typedef struct {
	char username[15];
	char password[8];
}Login;
#endif