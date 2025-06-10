#include <stdio.h>
#include <stdlib.h>

int topologicalOrder[10], topIndex = 0, hasCycle = 0;

void dfs(int adjacencyMatrix[][10], int numNodes, int visited[], int recStack[], int currentNode) {
    int neighbor;
    visited[currentNode] = 1;
    recStack[currentNode] = 1;//missed

    for (neighbor = 1; neighbor <= numNodes; neighbor++) {
        if (adjacencyMatrix[currentNode][neighbor]) {
            if (!visited[neighbor]) {
                dfs(adjacencyMatrix, numNodes, visited, recStack, neighbor);
            } else if (recStack[neighbor]) {
                hasCycle = 1; // Cycle detected
            }
        }
    }

    recStack[currentNode] = 0;//missed
    topologicalOrder[++topIndex] = currentNode;
}

int main() {
    int numNodes, adjacencyMatrix[10][10], i, visited[10] = {0}, recStack[10] = {0}, j;

    printf("\nEnter the number of nodes : ");
    scanf("%d", &numNodes);

    printf("Enter the adjacency matrix:\n");
    for (i = 1; i <= numNodes; i++)
        for (j = 1; j <= numNodes; j++)
            scanf("%d", &adjacencyMatrix[i][j]);

    printf("\nThe graph is as follows :\n");
    for (i = 1; i <= numNodes; i++) {
        for (j = 1; j <= numNodes; j++)
            printf("%d ", adjacencyMatrix[i][j]);
        printf("\n");
    }

    for (i = 1; i <= numNodes; i++) {
        if (visited[i] == 0) 
            dfs(adjacencyMatrix, numNodes, visited, recStack, i);
    }

    if (hasCycle) {
        printf("\nCycle detected! Topological ordering not possible.\n");
    } else {
        printf("\nTopological Ordering is : ");
        for (i = topIndex; i >= 1; i--)
            printf("%d ", topologicalOrder[i]);
        printf("\n");
    }

    return 0; 
}