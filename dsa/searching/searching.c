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
        printf("Enter Distance: ");
        scanf("%f", &newNode->distance);

        printf("Enter Rating: ");
        scanf("%f", &newNode->rating);

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

void display(struct Provider *head)
{
    struct Provider *temp = head;

    while (temp != NULL)
    {
        printf("\nID: %d", temp->id);
        printf("\nName: %s", temp->name);
        printf("\nService: %s", temp->service);
        printf("\nDistance: %.1f km", temp->distance);
        printf("\nRating: %.1f", temp->rating);
        printf("\nPrice: Rs. %.2f\n", temp->price);

        temp = temp->next;
    }
}

void searchService(struct Provider *head, char service[])
{
    struct Provider *temp = head;
    int found = 0;

    while (temp != NULL)
    {
        if (strcmp(temp->service, service) == 0)
        {
            printf("\nName: %s", temp->name);
            printf("\nDistance: %.1f km", temp->distance);
            printf("\nRating: %.1f", temp->rating);
            printf("\nPrice: Rs. %.2f\n", temp->price);

            found = 1;
        }

        temp = temp->next;
    }

    if (found == 0)
    {
        printf("\nNo provider found.");
    }
}
