#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define INF 999

int dist[MAX], parent[MAX];

void dijkstra(int src, int n, int adj[][MAX], int vis[])
{
    vis[src] = 1;
    for (int i = 1; i <= n; i++)
    {
        int u, mini = INF;
        for (int j = 1; j <= n; j++)
        {
            if (!vis[j] && dist[j] < mini)
            {
                mini = dist[j];
                u = j;
            }
        }
        vis[u] = 1;
        for (int v = 1; v <= n; v++)
        {
            if (!vis[v] && dist[v] > dist[u] + adj[u][v])
            {
                dist[v] = dist[u] + adj[u][v];
                parent[v] = u;
            }
        }
    }
}

void printPath(int node)
{
    if (parent[node] == -1)
    {
        printf("%d ", node);
        return;
    }
    printPath(parent[node]);
    printf("-> %d ", node);
}

int main()
{
    int n, src, adj[MAX][MAX], vis[MAX] = {0};
    printf("Enter no of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &adj[i][j]);
    printf("Enter the source (%d to %d):\n", 1, n);
    scanf("%d", &src);
    for (int i = 1; i <= n; i++)
    {
        dist[i] = adj[src][i];
        parent[i] = -1;
    }
    dijkstra(src, n, adj, vis);
    printf("\nShortest distance from %d\n", src);
    for (int i = 1; i <= n; i++)
    {
        printf("%d --> %d = %d\n", src, i, dist[i]);
        printf("%d -> ", src);
        printPath(i);
        printf("\n\n");
    }
    return 0;
}