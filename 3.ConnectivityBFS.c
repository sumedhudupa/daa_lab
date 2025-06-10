#include <stdio.h>
#include <stdlib.h>

void bfs(int adjacencyMatrix[][10], int numNodes, int visited[10], int startNode)
{
    int i, queue[10], front = 0, rear = -1, currentNode;
    visited[startNode] = 1;
    queue[++rear] = startNode;
    while (front <= rear)
    {
        currentNode = queue[front++];
        for (i = 1; i <= numNodes; i++)//i started from 0 so gave wrong output
        {
            if (!visited[i] && (adjacencyMatrix[currentNode][i] == 1))
            {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}

int main()
{
    int numNodes, adjacencyMatrix[10][10], i, visited[10] = {0}, j, componentCount = 0;
    printf("\nEnter the number of nodes : ");
    scanf("%d", &numNodes);
    printf("Enter the adjacency matrix:\n");
    for (i = 1; i <= numNodes; i++)
        for (j = 1; j <= numNodes; j++)
            scanf("%d", &adjacencyMatrix[i][j]);

    printf("\nThe graph is as follows :\n");
    for (i = 1; i <= numNodes; i++)
    {
        for (j = 1; j <= numNodes; j++)
            printf("%d ", adjacencyMatrix[i][j]);
        printf("\n"); 
    }

    for (i = 1; i <= numNodes; i++)
    {
        if (!visited[i])
        {
            bfs(adjacencyMatrix, numNodes, visited, i);
            componentCount++;
        }
    }
    if (componentCount == 1)
        printf("\nThe graph is connected\n");
    else
        printf("\nThe graph is not connected and has %d components\n", componentCount);
    return 0;
}
