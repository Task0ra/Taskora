#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Rental
{
    int id;
    char name[30];
    char category[20];
    float distance;
    float price;
    float rating;
    struct Rental *next;
};

struct Rental *createRentals(int n)
{
    struct Rental *head = NULL;
    struct Rental *temp = NULL;
    struct Rental *newNode;
    int i, choice;

    for(i = 0; i < n; i++)
    {
        newNode = (struct Rental *)malloc(sizeof(struct Rental));

        if(newNode == NULL)
        {
            printf("Memory allocation failed!\n");
            return head;
        }

        printf("\nEnter Rental ID: ");
        scanf("%d", &newNode->id);

        printf("Enter Rental Name/Model: ");
        scanf(" %29[^\n]", newNode->name);

        printf("\nSelect Rental Category:\n");
        printf("1. Room\n");
        printf("2. Flat\n");
        printf("3. Shop\n");
        printf("4. Bike\n");
        printf("5. Scooter\n");
        printf("6. Car\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                strcpy(newNode->category, "Room");
                break;
            case 2:
                strcpy(newNode->category, "Flat");
                break;
            case 3:
                strcpy(newNode->category, "Shop");
                break;
            case 4:
                strcpy(newNode->category, "Bike");
                break;
            case 5:
                strcpy(newNode->category, "Scooter");
                break;
            case 6:
                strcpy(newNode->category, "Car");
                break;
            default:
                printf("Invalid category!\n");
                free(newNode);
                i--;
                continue;
        }

        printf("Enter Distance in km: ");
        scanf("%f", &newNode->distance);

        printf("Enter Price per day: ");
        scanf("%f", &newNode->price);

        printf("Enter Rating: ");
        scanf("%f", &newNode->rating);

        newNode->next = NULL;

        if(head == NULL)
        {
            head = newNode;
            temp = newNode;
        }
        else
        {
            temp->next = newNode;
            temp = newNode;
        }
    }

    return head;
}
