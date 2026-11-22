#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Listing
{
    int id;
    char name[30];
    char type[20];
    char category[20];
    float distance;
    float price;

    struct Listing *next;
};

struct Listing *createListings(int n)
{
    struct Listing *head = NULL;
    struct Listing *newNode, *temp;

    int i, choice;

    for (i = 1; i <= n; i++)
    {
        newNode = (struct Listing *)malloc(sizeof(struct Listing));

        if (newNode == NULL)
        {
            printf("Memory allocation failed!\n");
            return head;
        }

        printf("\nEnter Listing ID: ");
        scanf("%d", &newNode->id);

        printf("Enter Name: ");
        scanf(" %29[^\n]", newNode->name);

        printf("\nSelect Type:\n");
        printf("1. Service\n");
        printf("2. Rental\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                strcpy(newNode->type, "Service");
                printf("Enter Service Category: ");
                scanf(" %19s", newNode->category);
                break;

            case 2:
                strcpy(newNode->type, "Rental");
                printf("Enter Rental Category: ");
                scanf(" %19s", newNode->category);
                break;

            default:
                printf("Invalid choice! Enter again.\n");
                free(newNode);
                i--;
                continue;
        }

        printf("Enter Distance (km): ");
        scanf("%f", &newNode->distance);

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
    }

    return head;
}

void findNearest(struct Listing *head)
{
    struct Listing *temp = head;
    struct Listing *nearest = NULL;

    int choice;
    char selectedType[20];

    printf("\nSelect what you want to search:\n");
    printf("1. Nearest Service Provider\n");
    printf("2. Nearest Rental\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        strcpy(selectedType, "Service");
    }
    else if (choice == 2)
    {
        strcpy(selectedType, "Rental");
    }
    else
    {
        printf("Invalid choice!\n");
        return;
    }

    while (temp != NULL)
    {
        if (strcmp(temp->type, selectedType) == 0)
        {
            if (nearest == NULL ||
                temp->distance < nearest->distance)
            {
                nearest = temp;
            }
        }

        temp = temp->next;
    }

    if (nearest == NULL)
    {
        printf("\nNo matching listing found!\n");
    }
    else
    {
        printf("\n----- NEAREST LISTING -----\n");
        printf("ID: %d\n", nearest->id);
        printf("Name: %s\n", nearest->name);
        printf("Type: %s\n", nearest->type);
        printf("Category: %s\n", nearest->category);
        printf("Distance: %.2f km\n", nearest->distance);
        printf("Price: %.2f\n", nearest->price);
    }
}

void displayListings(struct Listing *head)
{
    struct Listing *temp = head;

    while (temp != NULL)
    {
        printf("\nID: %d", temp->id);
        printf("\nName: %s", temp->name);
        printf("\nType: %s", temp->type);
        printf("\nCategory: %s", temp->category);
        printf("\nDistance: %.2f km", temp->distance);
        printf("\nPrice: %.2f\n", temp->price);

        temp = temp->next;
    }
}

void freeListings(struct Listing *head)
{
    struct Listing *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    struct Listing *head = NULL;
    int n;

    printf("Enter number of listings: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of listings!\n");
        return 0;
    }

    head = createListings(n);

    if (head == NULL)
    {
        printf("No listings created!\n");
        return 0;
    }

    printf("\nAll Listings:");
    displayListings(head);

    findNearest(head);

    freeListings(head);

    return 0;
}
