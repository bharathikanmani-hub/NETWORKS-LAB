#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int city;
    int cost;
    struct Node *next;
} Node;

void addEdge(Node **graph, int from, int to, int cost)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->city = to;
    newNode->cost = cost;
    newNode->next = graph[from];

    graph[from] = newNode;
}

void dfs(Node **graph, int city, int *visited, int *answer)
{
    Node *temp = graph[city];

    visited[city] = 1;

    while (temp != NULL)
    {
        if (!visited[temp->city])
        {
            *answer += temp->cost;

            dfs(graph, temp->city, visited, answer);
        }

        temp = temp->next;
    }
}

int minReorder(int n, int** connections, int connectionsSize,
               int* connectionsColSize)
{
    Node **graph = (Node **)calloc(n, sizeof(Node *));

    int i;

    for (i = 0; i < connectionsSize; i++)
    {
        int a = connections[i][0];
        int b = connections[i][1];

        addEdge(graph, a, b, 1);
        addEdge(graph, b, a, 0);
    }

    int *visited = (int *)calloc(n, sizeof(int));

    int answer = 0;

    dfs(graph, 0, visited, &answer);

    for (i = 0; i < n; i++)
    {
        Node *temp = graph[i];

        while (temp != NULL)
        {
            Node *next = temp->next;

            free(temp);

            temp = next;
        }
    }

    free(graph);
    free(visited);

    return answer;
}



