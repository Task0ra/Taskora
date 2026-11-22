#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record
{
    int id;
    char name[30];
    char category[20];
    char type[20];
    float price;

    struct Record *next;
};

struct Record *head = NULL;

// Insert a new record
void insertRecord()
{
    struct Record *newNode, *temp;

    newNode = (struct Record *)malloc(sizeof(struct Record));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Record ID: ");
    scanf("%d", &newNode->id);

    // Check duplicate ID
    temp = head;

    while (temp != NULL)
    {
        if (temp->id == newNode->id)
        {
            printf("Record ID already exists!\n");
            free(newNode);
            return;
        }

        temp = temp->next;
    }

    printf("Enter Name: ");
    scanf(" %29[^\n]", newNode->name);

    printf("Enter Category: ");
    scanf(" %19[^\n]", newNode->category);

    printf("Enter Type (Service/Rental): ");
    scanf(" %19s", newNode->type);

    printf("Enter Price: ");
    scanf("%f", &newNode->price);

    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    printf("\nRecord inserted successfully!\n");
}

// Delete a record using ID
void deleteRecord()
{
    struct Record *temp, *prev;
    int id;

    if (head == NULL)
    {
        printf("No records available!\n");
        return;
    }

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    temp = head;
    prev = NULL;

    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Record not found!\n");
        return;
    }

    if (prev == NULL)
    {
        head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }

    free(temp);

    printf("Record deleted successfully!\n");
}

// Display all records
void displayRecords()
{
    struct Record *temp = head;

    if (head == NULL)
    {
        printf("No records available!\n");
        return;
    }

    printf("\n----- TASKORA RECORDS -----\n");

    while (temp != NULL)
    {
        printf("\nID: %d", temp->id);
        printf("\nName: %s", temp->name);
        printf("\nCategory: %s", temp->category);
        printf("\nType: %s", temp->type);
        printf("\nPrice: %.2f\n", temp->price);

        temp = temp->next;
    }
}

// Search a record using ID
void searchRecord()
{
    struct Record *temp = head;
    int id;

    printf("Enter ID to search: ");
    scanf("%d", &id);

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            printf("\nRecord Found!\n");
            printf("ID: %d\n", temp->id);
            printf("Name: %s\n", temp->name);
            printf("Category: %s\n", temp->category);
            printf("Type: %s\n", temp->type);
            printf("Price: %.2f\n", temp->price);

            return;
        }

        temp = temp->next;
    }

    printf("Record not found!\n");
}

// Free memory
void freeRecords()
{
    struct Record *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    int choice;

    do
    {
        printf("\n===== TASKORA RECORD MANAGEMENT =====\n");
        printf("1. Insert Record\n");
        printf("2. Delete Record\n");
        printf("3. Display Records\n");
        printf("4. Search Record\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                insertRecord();
                break;

            case 2:
                deleteRecord();
                break;

            case 3:
                displayRecords();
                break;

            case 4:
                searchRecord();
                break;

            case 5:
                freeRecords();
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
