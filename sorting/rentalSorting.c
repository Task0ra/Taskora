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

void sortRentals(struct Rental *head, int choice)
{
    struct Rental *temp;
    int swapped;

    int id;
    char name[30], category[20];
    float distance, price, rating;

    if(head == NULL)
        return;

    do
    {
        swapped = 0;
        temp = head;

        while(temp->next != NULL)
        {
            int condition = 0;

            if(choice == 1 && temp->price > temp->next->price)
                condition = 1;

            else if(choice == 2 && temp->distance > temp->next->distance)
                condition = 1;

            else if(choice == 3 && temp->rating < temp->next->rating)
                condition = 1;

            if(condition)
            {
                id = temp->id;
                temp->id = temp->next->id;
                temp->next->id = id;

                strcpy(name, temp->name);
                strcpy(temp->name, temp->next->name);
                strcpy(temp->next->name, name);

                strcpy(category, temp->category);
                strcpy(temp->category, temp->next->category);
                strcpy(temp->next->category, category);

                distance = temp->distance;
                temp->distance = temp->next->distance;
                temp->next->distance = distance;

                price = temp->price;
                temp->price = temp->next->price;
                temp->next->price = price;

                rating = temp->rating;
                temp->rating = temp->next->rating;
                temp->next->rating = rating;

                swapped = 1;
            }

            temp = temp->next;
        }

    } while(swapped);
}

void displayRentals(struct Rental *head)
{
    struct Rental *temp = head;

    printf("\n----- SORTED RENTALS -----\n");

    while(temp != NULL)
    {
        printf("\nID: %d", temp->id);
        printf("\nName: %s", temp->name);
        printf("\nCategory: %s", temp->category);
        printf("\nDistance: %.2f km", temp->distance);
        printf("\nPrice: Rs. %.2f/day", temp->price);
        printf("\nRating: %.1f\n", temp->rating);

        temp = temp->next;
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
    int n, choice;

    printf("Enter number of rentals: ");
    scanf("%d", &n);

    if(n <= 0)
    {
        printf("Invalid number!\n");
        return 0;
    }

    head = createRentals(n);

    printf("\nSort By:\n");
    printf("1. Price (Low to High)\n");
    printf("2. Distance (Nearest First)\n");
    printf("3. Rating (Highest First)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if(choice < 1 || choice > 3)
    {
        printf("Invalid choice!\n");
        freeRentals(head);
        return 0;
    }

    sortRentals(head, choice);
    displayRentals(head);
    freeRentals(head);

    return 0;
}
