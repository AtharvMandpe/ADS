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

struct node* stack[100];
int stop = -1;

// stack functions declaration
void stackpush();
struct node* stackpop();
struct node* stacktop();

// queue functions declaration
void push();
void pop();
struct node *front();

// bst functions declaration

//1. TRAVERSALS
void inorder();
void preorder();
void postorder();
void inorderIterative();
void preorderIterative();
void postorderIterative();
void levelWise();

//2. OPERATIONS
struct node *insert();
struct node *deleteNode();
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

// queue operations
void pop()
{
    f++;
}

struct node *front()
{
    return queue[f];
}


// stack operations
void stackpush(struct node* temp){
    stack[++stop] = temp;
}

struct node* stackpop(){
    return stack[stop--];
}

struct node* stacktop(){
    return stack[stop];
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



//TRAVERSALS
void inorder(struct node* root){
    if(root == NULL){
        return;
    }

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct node* root){
    if(root == NULL){
        return;
    }

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct node* root){
    if(root == NULL){
        return;
    }

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void inorderIterative(struct node* root){
    while(root != NULL){
        stackpush(root);
        root = root->left;
    }

    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp = stackpop();
    printf("%d ", temp->data);

    while(stop != -1){
        temp = stackpop();
        printf("%d ", temp->data);

        if(temp->right != NULL){
            temp = temp->right;
            stackpush(temp);
            temp = temp->left;
            while(temp != NULL){
                stackpush(temp);
                temp = temp->left;
            }
        }
    }
}

void preorderIterative(struct node* root){
    while(root != NULL){
        stackpush(root);
        printf("%d ", root->data);
        root = root->left;
    }

    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp = stackpop();

    while(stop != -1){
        temp = stackpop();

        if(temp->right != NULL){
            temp = temp->right;
            stackpush(temp);
            printf("%d ", temp->data);
            temp = temp->left;
            while(temp != NULL){
                stackpush(temp);
                printf("%d ", temp->data);
                temp = temp->left;
            }
        }
    }
}

void postorderIterative(struct node* root){
    struct node* prev = NULL;
    do{
        while(root != NULL){
            stackpush(root);
            root = root->left;
        }

        while(root == NULL && stop != -1){
            root = stacktop();
            if(root->right == NULL || root->right == prev){
                printf("%d ", root->data);
                prev = root;
                root = stackpop();
                root = NULL;
            }
            else{
                root = root->right;
            }
        }
    }while(stop != -1);
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