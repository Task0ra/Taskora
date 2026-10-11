#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Provider
{
    int id;
    char name[30];
    char service[20];
    float distance;
    float rating;
    float price;

    struct Provider *next;
};

struct Provider *createProvider(int n)
{
    struct Provider *head = NULL;
    struct Provider *newNode;
    struct Provider *temp;

    int choice;

    for (int i = 0; i < n; i++)
    {
        newNode = (struct Provider *)malloc(sizeof(struct Provider));

        printf("\nEnter ID: ");
        scanf("%d", &newNode->id);

        printf("Enter Name: ");
        scanf(" %[^\n]", newNode->name);

        printf("\nSelect Service:");
        printf("\n1. Electrician");
        printf("\n2. Plumber");
        printf("\n3. Maid");
        printf("\n4. House Help");
        printf("\n5. Nurse");
        printf("\n6. Decoration");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                strcpy(newNode->service, "electrician");
                break;

            case 2:
                strcpy(newNode->service, "plumber");
                break;

            case 3:
                strcpy(newNode->service, "maid");
                break;

            case 4:
                strcpy(newNode->service, "house help");
                break;

            case 5:
                strcpy(newNode->service, "nurse");
                break;

            case 6:
                strcpy(newNode->service, "decoration");
                break;

            default:
                printf("Invalid choice!");
                free(newNode);
                i--;
                continue;
        }
