#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Action
{
    int actionID;
    char customerName[30];
    char actionType[30];
    char itemName[30];

    struct Action *next;
};

struct Action *top = NULL;

// PUSH: Add a new action
void pushAction()
{
    struct Action *newNode;

    newNode = (struct Action *)malloc(sizeof(struct Action));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Action ID: ");
    scanf("%d", &newNode->actionID);

    printf("Enter Customer Name: ");
    scanf(" %29[^\n]", newNode->customerName);

    printf("\nSelect Action Type:\n");
    printf("1. Booking Created\n");
    printf("2. Booking Cancelled\n");
    printf("3. Booking Updated\n");
    printf("Enter choice: ");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            strcpy(newNode->actionType, "Booking Created");
            break;

        case 2:
            strcpy(newNode->actionType, "Booking Cancelled");
            break;

        case 3:
            strcpy(newNode->actionType, "Booking Updated");
            break;

        default:
            printf("Invalid choice!\n");
            free(newNode);
            return;
    }

    printf("Enter Service/Rental Name: ");
    scanf(" %29[^\n]", newNode->itemName);

    newNode->next = top;
    top = newNode;

    printf("\nAction added successfully!\n");
}

// POP: Remove the latest action
void popAction()
{
    struct Action *temp;

    if (top == NULL)
    {
        printf("\nNo actions available!\n");
        return;
    }

    temp = top;

    printf("\nLatest Action Removed:\n");
    printf("Action ID: %d\n", temp->actionID);
    printf("Customer: %s\n", temp->customerName);
    printf("Action: %s\n", temp->actionType);
    printf("Item: %s\n", temp->itemName);

    top = top->next;

    free(temp);
}

// Display all actions
void displayActions()
{
    struct Action *temp = top;

    if (top == NULL)
    {
        printf("\nNo actions available!\n");
        return;
    }

    printf("\n--- Recent Actions ---\n");

    while (temp != NULL)
    {
        printf("\nAction ID: %d", temp->actionID);
        printf("\nCustomer: %s", temp->customerName);
        printf("\nAction: %s", temp->actionType);
        printf("\nItem: %s\n", temp->itemName);

        temp = temp->next;
    }
}

// Free remaining memory
void freeStack()
{
    struct Action *temp;

    while (top != NULL)
    {
        temp = top;
        top = top->next;
        free(temp);
    }
}

int main()
{
    int choice;

    do
    {
        printf("\n===== TASKORA ACTION STACK =====\n");
        printf("1. Add New Action (PUSH)\n");
        printf("2. Remove Latest Action (POP)\n");
        printf("3. Display Recent Actions\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                pushAction();
                break;

            case 2:
                popAction();
                break;

            case 3:
                displayActions();
                break;

            case 4:
                freeStack();
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
