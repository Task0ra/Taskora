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

void searchRental(Rental *head)
{
    Rental *temp = head;
    int choice;
    int found = 0;
    char category[20];

    printf("\nSearch Rental By Category:\n");
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
            strcpy(category, "Room");
            break;

        case 2:
            strcpy(category, "Flat");
            break;

        case 3:
            strcpy(category, "Shop");
            break;

        case 4:
            strcpy(category, "Bike");
            break;

        case 5:
            strcpy(category, "Scooter");
            break;

        case 6:
            strcpy(category, "Car");
            break;

        default:
            printf("Invalid search choice!\n");
            return;
    }

    while(temp != NULL)
    {
        if(strcmp(temp->category, category) == 0 &&
           temp->available == 1)
        {
            printf("\nRental Found!\n");
            printf("ID: %d\n", temp->id);
            printf("Name/Model: %s\n", temp->name);
            printf("Category: %s\n", temp->category);
            printf("Location: %s\n", temp->location);
            printf("Distance: %.2f km\n", temp->distance);
            printf("Price per day: Rs. %.2f\n", temp->price);
            printf("Rating: %.1f\n", temp->rating);

            found = 1;
        }

        temp = temp->next;
    }

    if(found == 0)
    {
        printf("\nNo available rental found in this category.\n");
    }
}

void displayRentals(Rental *head)
{
    Rental *temp = head;

    printf("\n----- ALL RENTAL LISTINGS -----\n");

    while(temp != NULL)
    {
        printf("\nID: %d\n", temp->id);
        printf("Name/Model: %s\n", temp->name);
        printf("Category: %s\n", temp->category);
        printf("Location: %s\n", temp->location);
        printf("Distance: %.2f km\n", temp->distance);
        printf("Price per day: Rs. %.2f\n", temp->price);
        printf("Rating: %.1f\n", temp->rating);
        printf("Availability: %s\n",
               temp->available == 1 ? "Available" : "Not Available");

        temp = temp->next;
    }
}

void freeRentals(Rental *head)
{
    Rental *temp;

    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    Rental *head;
    int n;

    printf("Enter number of rental listings: ");
    scanf("%d", &n);

    if(n <= 0)
    {
        printf("Invalid number of listings!\n");
        return 0;
    }

    head = createRentals(n);

    displayRentals(head);

    searchRental(head);

    freeRentals(head);

    return 0;
}
