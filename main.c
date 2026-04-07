#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Ticket Node
struct Ticket
{
    int id;
    char issue[100];
    char status[20];
    struct Ticket *left, *right;
};

// Create Ticket Node
struct Ticket *createTicket(int id, char issue[], char status[])
{
    struct Ticket *newNode = (struct Ticket *)malloc(sizeof(struct Ticket));
    newNode->id = id;
    strcpy(newNode->issue, issue);
    strcpy(newNode->status, status);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert Ticket (BST)
struct Ticket *insert(struct Ticket *root, int id, char issue[], char status[])
{
    if (root == NULL)
        return createTicket(id, issue, status);

    if (id < root->id)
        root->left = insert(root->left, id, issue, status);
    else
        root->right = insert(root->right, id, issue, status);

    return root;
}

// Search Ticket
struct Ticket *search(struct Ticket *root, int id)
{
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return search(root->left, id);
    else
        return search(root->right, id);
}

// Find Minimum (for deletion)
struct Ticket *findMin(struct Ticket *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete Ticket
struct Ticket *delete(struct Ticket *root, int id)
{
    if (root == NULL)
        return root;

    if (id < root->id)
        root->left = delete(root->left, id);
    else if (id > root->id)
        root->right = delete(root->right, id);
    else
    {
        if (root->left == NULL)
        {
            struct Ticket *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Ticket *temp = root->left;
            free(root);
            return temp;
        }

        struct Ticket *temp = findMin(root->right);
        root->id = temp->id;
        strcpy(root->issue, temp->issue);
        strcpy(root->status, temp->status);
        root->right = delete(root->right, temp->id);
    }
    return root;
}

// Display Tickets (Inorder)
void display(struct Ticket *root)
{
    if (root != NULL)
    {
        display(root->left);
        printf("\nID: %d | Issue: %s | Status: %s", root->id, root->issue, root->status);
        display(root->right);
    }
}

// Update Ticket
void update(struct Ticket *root, int id)
{
    struct Ticket *t = search(root, id);
    if (t == NULL)
    {
        printf("\nTicket not found!");
        return;
    }
    printf("\nEnter new status: ");
    scanf("%s", t->status);
    printf("Updated successfully!\n");
}

// Main Menu
int main()
{
    struct Ticket *root = NULL;
    int choice, id;
    char issue[100], status[20];

    while (1)
    {
        printf("\n\n--- Customer Support System ---");
        printf("\n1. Create Ticket");
        printf("\n2. View All Tickets");
        printf("\n3. Search Ticket");
        printf("\n4. Update Ticket");
        printf("\n5. Delete Ticket");
        printf("\n6. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter Ticket ID: ");
            scanf("%d", &id);
            printf("Enter Issue: ");
            scanf(" %[^\n]", issue);
            printf("Enter Status: ");
            scanf("%s", status);
            root = insert(root, id, issue, status);
            break;

        case 2:
            display(root);
            break;

        case 3:
        {
            printf("Enter Ticket ID: ");
            scanf("%d", &id);
            struct Ticket *t = search(root, id);
            if (t)
                printf("\nFound -> ID: %d | Issue: %s | Status: %s", t->id, t->issue, t->status);
            else
                printf("\nTicket not found!");
            break;
        }

        case 4:
            printf("Enter Ticket ID: ");
            scanf("%d", &id);
            update(root, id);
            break;

        case 5:
            printf("Enter Ticket ID: ");
            scanf("%d", &id);
            root = delete(root, id);
            break;

        case 6:
            exit(0);

        default:
            printf("\nInvalid choice!");
        }
    }
}