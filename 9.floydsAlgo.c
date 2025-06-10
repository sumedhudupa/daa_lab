#include <stdio.h>
#define INF 9999
#define MAX 10

int min(int a, int b)
{
    return (a < b) ? a : b;
}

void floyd(int graph[MAX][MAX], int n)
{
    int i, j, k;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

int main()
{
    int n, i, j;
    int graph[MAX][MAX];
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
            if (i != j && graph[i][j] == -1)
                graph[i][j] = INF;
        }
    floyd(graph, n);
    printf("Shortest distances between every pair of vertices:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
    return 0;
}
