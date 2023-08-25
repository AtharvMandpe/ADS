#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// structure for adjacency list
struct node
{
    int weight;
    int vertex;
    struct node *next;
};

int queue[MAX_SIZE];
int front = -1;
int rear = -1;

int stack[MAX_SIZE];
int top = -1;

void push();
void pop();
int stacktop();
int emptyStack();
void enqueue();
int dequeue();
void BFSadjmat();
void BFSadjlist();
void DFSadjmat();
void DFSadjlist();
int emptyQueue();
void prims();
int mini();

int main()
{

    // creating adj list
    struct node *g[10];

    int v;
    printf("\nhow many edges ? ");
    scanf("%d", &v);

    for (int i = 0; i < 10; i++)
    {
        g[i] = NULL;
    }

    struct node *temp;
    for (int i = 0; i < v; i++)
    {
        int s, d, w;
        printf("\nenter src, dest and wt : ");
        scanf("%d %d %d", &s, &d, &w);

        struct node *nn = (struct node *)malloc(sizeof(struct node));
        nn->vertex = d;
        nn->weight = w;
        nn->next = NULL;

        if (g[s] == NULL)
        {
            g[s] = nn;
        }
        else
        {
            struct node *p = g[s];
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = nn;
        }

        struct node* nn1 = (struct node *)malloc(sizeof(struct node));
        nn1->vertex = s;
        nn1->weight = w;
        nn1->next = NULL;

        if (g[d] == NULL)
        {
            g[d] = nn1;
        }
        else
        {
            struct node *p = g[d];
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = nn1;
        }
    }

    int gh[][8] = {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 1},
        {0, 0, 0, 0, 0, 1, 1, 0}};

    int m[][5] = {
        {0, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0}};

    int prim[][5] = {
        {99, 2, 3, 6, 2},
        {2, 99, 7, 99, 2},
        {3, 7, 99, 4, 3},
        {6, 99, 4, 99, 1},
        {2, 2, 3, 1, 99}};
    int p = 5;
    int l = 5;
    int n = 8;

    // BFSadjmat(n, g);
    // DFSadjmat(l, m);
    DFSadjlist(g, v);
    // prims(p, prim);

    return 0;
}

// stack opertions
void push(int n)
{
    if (top >= MAX_SIZE)
    {
        printf("stack full");
        return;
    }
    stack[++top] = n;
}

void pop()
{
    if (top == -1)
    {
        printf("stack empty");
        return;
    }
    top--;
}

int stacktop()
{
    if (top == -1)
    {
        printf("stack empty");
        return -1;
    }
    return stack[top];
}

int emptyStack()
{
    if (top == -1)
    {
        return 1;
    }
    return 0;
}

// queue opertions
void enqueue(int element)
{
    if (rear == MAX_SIZE - 1)
    {
        printf("Queue is full");
        return;
    }
    if (front == -1)
    {
        front = 0;
    }
    queue[++rear] = element;
}

int dequeue()
{
    if (front == -1 || front > rear)
    {
        printf("Queue is empty");
        return -1;
    }
    int element = queue[front++];
    return element;
}

int emptyQueue()
{
    if (front == -1 || front > rear)
    {
        return 1;
    }
    return 0;
}

// bfs using adj matrix
void BFSadjmat(int n, int g[][n])
{
    int v;
    int visited[10] = {0};

    printf("enter start vertex : ");
    scanf("%d", &v);

    visited[v] = 1;
    enqueue(v);

    while (emptyQueue() == 0)
    {
        v = dequeue();
        printf("%d ", v);
        for (int i = 0; i < n; i++)
        {
            if (g[v][i] == 1 && visited[i] == 0)
            {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

// bfs using adj list

// dfs using adj matrix
void DFSadjmat(int n, int g[][n])
{
    int v, i;
    int visited[10] = {0};

    printf("enter start vertex : ");
    scanf("%d", &v);

    push(v);
    visited[v] = 1;

    printf("%d ", v);

    do
    {
        for (i = 0; i < n; i++)
        {
            if (g[v][i] == 1 && visited[i] == 0)
            {
                printf("%d ", i);
                push(i);
                visited[i] = 1;
                v = i;
                break;
            }
        }

        if (i == n)
        {
            pop();
            if (emptyStack() == 0)
            {
                v = stack[top];
            }
        }
    } while (emptyStack() == 0);
}

// dfs using adj list
void DFSadjlist(struct node *g[], int n)
{
    int visited[10], v, i;
    struct node *p;
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    printf("\nenter start vertex : ");
    scanf("%d", &v);

    push(v);
    visited[v] = 1;
    printf("%d ", v);

    do
    {
        p = g[v];
        while (p != NULL)
        {
            if (visited[p->vertex] == 0)
            {
                printf("%d ", p->vertex);
                push(p->vertex);
                visited[p->vertex] = 1;
                v = p->vertex;
                break;
            }
            else
            {
                p = p->next;
            }

            if (p == NULL)
            {
                pop();
                if (!emptyStack())
                {
                    v = stack[top];
                }
            }
        }
    } while (!emptyStack());
}

// prims algorithm
void prims(int p, int prim[][p])
{
    int visited[10];
    int distance[10];
    int parent[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int u, i, j, v;

    for (int i = 0; i < 10; i++)
    {
        visited[i] = 0;
        distance[i] = 99;
    }

    printf("enter start vertex : ");
    scanf("%d", &v);
    distance[v] = 0;

    for (i = 0; i < p - 1; i++)
    {
        u = mini(distance, visited);
        visited[u] = 1;

        for (j = 0; j < p; j++)
        {
            if (prim[u][j] < distance[j] && visited[j] == 0)
            {
                distance[j] = prim[u][j];
                parent[j] = u;
            }
        }

        // display visited and distance and parent array
        for (int k = 0; k < p; k++)
        {
            printf("%d ", visited[k]);
        }
        printf("\n");
        for (int k = 0; k < p; k++)
        {
            printf("%d ", distance[k]);
        }
        printf("\n");
        for (int k = 0; k < p; k++)
        {
            printf("%d ", parent[k]);
        }
        printf("\n");
        printf("\n");
    }
}

int mini(int distance[10], int visited[10])
{
    int index, min = 99;

    for (int i = 0; i < 10; i++)
    {
        if (distance[i] < min && visited[i] == 0)
        {
            min = distance[i];
            index = i;
        }
    }

    return index;
}
