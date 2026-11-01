#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Rental
{
    int id;
    char name[50];
    char category[20];
    char location[50];
    float distance;
    float price;
    float rating;
    int available;

    struct Rental *next;
} Rental;

Rental *createRentals(int n)
{
    Rental *head = NULL;
    Rental *temp = NULL;
    Rental *newNode;
    int i, choice;

    for(i = 0; i < n; i++)
    {
        newNode = (Rental *)malloc(sizeof(Rental));

        if(newNode == NULL)
        {
            printf("Memory allocation failed!\n");
            return head;
        }

        printf("\nEnter Rental ID: ");
        scanf("%d", &newNode->id);

        printf("Enter Rental Name/Model: ");
        scanf(" %49[^\n]", newNode->name);

        printf("\nSelect Rental Category:\n");
        printf("1. Room\n");
        printf("2. Flat\n");
        printf("3. Shop\n");
        printf("4. Bike\n");
        printf("5. Scooter\n");
        printf("6. Car\n");

        printf("Enter your choice: ");
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
                printf("Invalid category! Enter this rental again.\n");
                free(newNode);
                i--;
                continue;
        }

        printf("Enter Location: ");
        scanf(" %49[^\n]", newNode->location);

        printf("Enter Distance in km: ");
        scanf("%f", &newNode->distance);

        printf("Enter Price per day: ");
        scanf("%f", &newNode->price);

        printf("Enter Rating (0-5): ");
        scanf("%f", &newNode->rating);

        printf("Available? (1 = Yes, 0 = No): ");
        scanf("%d", &newNode->available);

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
