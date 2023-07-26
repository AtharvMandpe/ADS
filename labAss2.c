#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *queue[100];
int rear = -1;
int f = -1;

// queue functions declaration
void push();
void pop();
struct node *front();

// bst functions declaration
void inorder();
struct node *insert();
struct node *deleteNode();
void levelWise();
int height();
void leafNodes();
struct node *mirrorImage();

int main()
{
    struct node *root = NULL;

    int da;
    int choice;
    while (1)
    {
        printf("\n\n1. Insert\n2. Delete\n3. Mirror Image\n4. Level Wise Display\n5. Height\n6. Leaf Nodes\n7. Exit\n\n");
        printf("\nEnter choice : \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter data : \n");
            scanf("%d", &da);
            root = insert(root, da);
            break;

        case 2:
            printf("\nEnter data : \n");
            scanf("%d", &da);
            root = deleteNode(root, da);
            break;

        case 3:
            root = mirrorImage(root);
            printf("\nLevel Wise Display Of Mirrored Tree: \n");
            levelWise(root);
            break;

        case 4:
            printf("\nLevel Wise Display : \n");
            levelWise(root);
            break;

        case 5:
            da = height(root);
            printf("\nHeight : %d\n", da);
            break;

        case 6:
            printf("\nLeaf Nodes : \n");
            leafNodes(root);
            break;

        case 7:
            exit(0);
        }
    }
}

void push(struct node *root)
{
    if (f == -1 && rear == -1)
    {
        f = 0;
        rear = 0;
        queue[rear] = root;
    }
    else
    {
        queue[++rear] = root;
    }
}

void pop()
{
    f++;
}

struct node *front()
{
    return queue[f];
}

// deleting node
struct node *deleteNode(struct node *root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (data == root->data)
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node *temp = root->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    else if (data > root->data)
    {
        root->right = deleteNode(root->right, data);
    }
    else
    {
        root->left = deleteNode(root->left, data);
    }

    return root;
}

// inserting node
struct node *insert(struct node *root, int d)
{
    if (root == NULL)
    {
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        temp->data = d;
        temp->left = NULL;
        temp->right = NULL;

        return temp;
    }
    if (d < root->data)
    {
        root->left = insert(root->left, d);
    }
    else
    {
        root->right = insert(root->right, d);
    }

    return root;
}

// level order traversal ( BFS )
void levelWise(struct node *root)
{
    int front = -1;
    int rear = -1;
    int current = 1;
    int next = 0;

    queue[++rear] = root;

    while (front != rear)
    {
        struct node *fr = queue[++front];

        current--;

        if (fr == NULL)
        {
            printf("NULL ");
        }
        else
        {
            printf("%d ", fr->data);
            if (fr->left)
            {
                queue[++rear] = fr->left;
                next++;
            }
            if (fr->right)
            {
                queue[++rear] = fr->right;
                next++;
            }
        }

        if (current == 0)
        {
            printf("\n");
            current = next;
            next = 0;
        }
    }
}

// height of bst
int height(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    int left = 1 + height(root->left);
    int right = 1 + height(root->right);

    if (left >= right)
    {
        return left;
    }
    return right;
}

// display leaf nodes
void leafNodes(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left == NULL && root->right == NULL)
    {
        printf("%d ", root->data);
        return;
    }
    leafNodes(root->left);
    leafNodes(root->right);
}

// mirror image of bst
struct node *mirrorImage(struct node *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    struct node *temp = root->left;
    root->left = mirrorImage(root->right);
    root->right = mirrorImage(temp);

    return root;
}