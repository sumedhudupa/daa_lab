/*
Aim: Let there be N workers and N jobs.
Any worker can be assigned to perform any job,
incurring some cost that may vary depending on the work-job assignment.
It is required to perform all jobs by assigning exactly one worker to each job and
exactly one job to each agent in such a way that the total cost of the assignment is minimized.
*/

// Program to solve Job Assignment problem
// using Branch and Bound
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define N 4

typedef struct Node {
    struct Node *parent;
    int worker, job, pathCost, totalCost;
    bool jobAssigned[N];
} Node;
//pathcost is actual cost, totalcost is pathcost + lowerbound = estimated cost

Node *createNode(int worker, int job, bool jobAssigned[], Node *parent) {
    Node *node = (Node *)malloc(sizeof(Node));
    for (int i = 0; i < N; i++)
        node->jobAssigned[i] = jobAssigned[i];
    if (job != -1) node->jobAssigned[job] = true;
    node->parent = parent;
    node->worker = worker;
    node->job = job;
    return node;
}

int calculateLowerBound(int cost[N][N], int worker, bool jobAssigned[]) {
    int bound = 0;
    bool jobAvailable[N];
    for (int i = 0; i < N; i++) jobAvailable[i] = true;
    for (int w = worker + 1; w < N; w++) {
        int minCost = INT_MAX, minJob = -1;
        for (int j = 0; j < N; j++) {
            if (!jobAssigned[j] && jobAvailable[j] && cost[w][j] < minCost) {
                minCost = cost[w][j];
                minJob = j;
            }
        }
        bound += minCost;
        if (minJob != -1) jobAvailable[minJob] = false;
    }
    return bound;
}

void printPath(Node *node) {
    if (!node || node->parent == NULL) return;
    printPath(node->parent);
    printf("Assign Worker %c to Job %d\n", node->worker + 'A', node->job + 1);
}

int findMinAssignmentCost(int cost[N][N]) {
    Node *queue[N*N];
    int size = 0;
    bool jobAssigned[N] = {false};
    Node *root = createNode(-1, -1, jobAssigned, NULL);
    root->pathCost = root->totalCost = 0;
    queue[size++] = root;

    while (size > 0) {
        int minIdx = 0;
        for (int i = 1; i < size; i++)
            if (queue[i]->totalCost < queue[minIdx]->totalCost)
                minIdx = i;
        Node *curr = queue[minIdx];
        queue[minIdx] = queue[--size];

        int nextWorker = curr->worker + 1;
        if (nextWorker == N) {
            printPath(curr);
            return curr->totalCost;
        }
        for (int j = 0; j < N; j++) {
            if (!curr->jobAssigned[j]) {
                Node *child = createNode(nextWorker, j, curr->jobAssigned, curr);
                child->pathCost = curr->pathCost + cost[nextWorker][j];
                child->totalCost = child->pathCost + calculateLowerBound(cost, nextWorker, child->jobAssigned);
                queue[size++] = child;
            }
        }
    }
    return -1;
}

int main() {
    int cost[N][N] = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };
    printf("Optimal Cost is %d\n", findMinAssignmentCost(cost));
    return 0;
}

/*
OUTPUT:
Cost Matrix:
        Job 1   Job 2   Job 3   Job 4
A       9       2       7       8
B       6       4       3       7
C       5       8       1       8
D       7       6       9       4

Assign Worker A to Job 1
Assign Worker B to Job 0
Assign Worker C to Job 2
Assign Worker D to Job 3

Optimal Cost is 13
*/
