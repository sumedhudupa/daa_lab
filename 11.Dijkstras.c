#include <stdio.h>
#define INFINITY 999

void dijkstra(int cost[10][10], int n, int source, int v[10], int d[10], int parent[10])//wrote wrong
{
    int min, i, j, u;
    v[source] = 1;
    for (i = 1; i <= n; i++)
        parent[i] = source; // Initialize parent

    for (i = 1; i <= n; i++)
    {
        min = INFINITY;
        for (j = 1; j <= n; j++)
        {
            if (v[j] == 0 && d[j] < min)
            {
                min = d[j];
                u = j;
            }
        }
        v[u] = 1;
        for (j = 1; j <= n; j++)
        {
            if (v[j] == 0 && (d[j] > (d[u] + cost[u][j])))
            {
                d[j] = d[u] + cost[u][j];
                parent[j] = u; // Update parent
            }
        }
    }
}

void printPath(int parent[], int j)
{
    if (parent[j] == j) {
        printf("%d", j);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

int main()
{
    int n;
    int cost[10][10];
    int sourceNode;
    int v[10];
    int d[10];
    int parent[10];
    int i, j;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter Cost Adjacency matrix:\n");
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &cost[i][j]);
    printf("Enter the source (%d to %d):\n", 1, n);
    scanf("%d", &sourceNode);
    for (i = 1; i <= n; i++)//missed
    {
        d[i] = cost[sourceNode][i];
        v[i] = 0;
        parent[i] = sourceNode;
    }
    parent[sourceNode] = sourceNode;//missed
    dijkstra(cost, n, sourceNode, v, d, parent);
    printf("Shortest distance from %d\n\n", sourceNode);
    for (i = 1; i <= n; i++) {
        printf("%d --> %d = %d, Path: ", sourceNode, i, d[i]);
        printPath(parent, i);
        printf("\n");
    }
    return 0;
}