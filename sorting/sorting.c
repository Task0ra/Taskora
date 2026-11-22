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

void Sorting(struct Provider *head, int choice)
{
    struct Provider *i;
    struct Provider *j;

    int tempId;
    char tempName[30];
    char tempService[20];

    float tempDistance;
    float tempRating;
    float tempPrice;

    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            int swap = 0;

            //Sort by Distance
            if (choice == 1 && i->distance > j->distance)
            {
                swap = 1;
            }

            // Sort by Price 
            if (choice == 2 && i->price > j->price)
            {
                swap = 1;
            }

            // Sort by Rating 
            if (choice == 3 && i->rating < j->rating)
            {
                swap = 1;
            }

            if (swap == 1)
            {
                // Swap ID 
                tempId = i->id;
                i->id = j->id;
                j->id = tempId;

                // Swap Name 
                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

                // Swap Service 
                strcpy(tempService, i->service);
                strcpy(i->service, j->service);
                strcpy(j->service, tempService);

                // Swap Distance 
                tempDistance = i->distance;
                i->distance = j->distance;
                j->distance = tempDistance;

                // Swap Rating 
                tempRating = i->rating;
                i->rating = j->rating;
                j->rating = tempRating;

                // Swap Price 
                tempPrice = i->price;
                i->price = j->price;
                j->price = tempPrice;
            }
        }
    }
}

int main()
{
    struct Provider *head = NULL;

    int n;
    int choice;

    printf("Enter number of providers: ");
    scanf("%d", &n);

    head = createProvider(n);

    printf("\n\n===== ALL PROVIDERS =====\n");
    display(head);

    printf("\n===== SORT PROVIDERS =====");
    printf("\n1. Sort by Distance");
    printf("\n2. Sort by Price");
    printf("\n3. Sort by Rating");

    printf("\n\nEnter choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3)
    {
        printf("\nInvalid choice.");
        return 0;
    }

    Sorting(head, choice);

    printf("\n\n===== SORTED PROVIDERS =====\n");
    display(head);

    return 0;
}
