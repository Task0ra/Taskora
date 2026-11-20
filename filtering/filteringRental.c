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
                printf("Invalid category! Try again.\n");
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

void filterRentals(struct Rental *head)
{
    struct Rental *temp = head;

    int choice, found = 0;

    float maxPrice, maxDistance, minRating;
    char category[20];

    printf("\nFilter Rentals By Category:\n");
    printf("1. Room\n");
    printf("2. Flat\n");
    printf("3. Shop\n");
    printf("4. Bike\n");
    printf("5. Scooter\n");
    printf("6. Car\n");
    printf("7. All Rentals\n");

    printf("Enter choice: ");
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

        case 7:
            strcpy(category, "All");
            break;

        default:
            printf("Invalid choice!\n");
            return;
    }

    printf("\nEnter Maximum Price per day: ");
    scanf("%f", &maxPrice);

    printf("Enter Maximum Distance in km: ");
    scanf("%f", &maxDistance);

    printf("Enter Minimum Rating: ");
    scanf("%f", &minRating);

    printf("\n----- FILTERED RENTALS -----\n");

    while(temp != NULL)
    {
        if((strcmp(category, "All") == 0 ||
            strcmp(temp->category, category) == 0) &&
            temp->price <= maxPrice &&
            temp->distance <= maxDistance &&
            temp->rating >= minRating)
        {
            printf("\nRental ID: %d", temp->id);
            printf("\nName: %s", temp->name);
            printf("\nCategory: %s", temp->category);
            printf("\nDistance: %.2f km", temp->distance);
            printf("\nPrice: Rs. %.2f/day", temp->price);
            printf("\nRating: %.1f\n", temp->rating);

            found = 1;
        }

        temp = temp->next;
    }

    if(found == 0)
    {
        printf("\nNo rental found matching your requirements.\n");
    }
}

void freeRentals(struct Rental *head)
{
    struct Rental *temp;

    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    struct Rental *head;
    int n;

    printf("Enter number of rentals: ");
    scanf("%d", &n);

    if(n <= 0)
    {
        printf("Invalid number!\n");
        return 0;
    }

    head = createRentals(n);

    if(head == NULL)
    {
        printf("No rental records created.\n");
        return 0;
    }

    filterRentals(head);

    freeRentals(head);

    return 0;
}
