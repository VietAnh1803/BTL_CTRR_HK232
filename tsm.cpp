#include "tsm.h"

// Global variables defined here
int DEM = 0;  // Counter for the number of recursive calls
int COUNT = 0;  // Counter for the number of times a better solution is found

// Helper function for the Branch and Bound algorithm
// G: adjacency matrix, n: number of cities, startCity: starting city index
// i: current depth in the search tree, minCost: minimum edge cost
// tmpRes: current path cost, result: best path cost so far
// tempPath: current path being explored, path: best path found so far
// visited: array to keep track of visited cities
void branchBoundHelp(int G[MAXN][MAXN], int n, int startCity, int i, int minCost, int& tmpRes, int& result, int tempPath[], int path[], int visited[]) {
    ++DEM;  // Increment the recursive call counter

    for (int city = 0; city < n; city++) {
        if (visited[city] == 0) {  // If the city hasn't been visited yet
            visited[city] = 1;  // Mark the city as visited
            tempPath[i] = city;  // Add the city to the current path
            tmpRes += G[tempPath[i - 1]][tempPath[i]];  // Add the cost of the edge to the current path cost

            if (i == n - 1) {  // If all cities are visited (last city)
                int candidate = tmpRes + G[tempPath[i]][startCity];  // Total cost including return to start
                if (result > candidate) {  // If this path is better than the best so far
                    ++COUNT;  // Increment the counter for better solutions found
                    result = candidate;  // Update the best result
                    for (int j = 0; j < n; j++) {
                        path[j] = tempPath[j];  // Copy the current path as the best path
                    }
                }
            } else if (tmpRes + (n - i - 1) * minCost < result) {  // Pruning condition
                // If the current cost plus the minimum possible cost for remaining edges
                // is less than the best result, continue searching this branch
                branchBoundHelp(G, n, startCity, i + 1, minCost, tmpRes, result, tempPath, path, visited);
            }
            visited[city] = 0;  // Backtrack: mark the city as unvisited
            tmpRes -= G[tempPath[i - 1]][tempPath[i]];  // Backtrack: remove the edge cost
        }
    }
}

// Main function for the Branch and Bound algorithm
// G: adjacency matrix, n: number of cities, start: starting city character
string branchBound(int G[MAXN][MAXN], int n, char start) {
    int minCost = INT_MAX;  // Initialize minimum edge cost
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                minCost = min(minCost, G[i][j]);  // Find the minimum edge cost
            }
        }
    }

    int tmpRes = 0, Res = INT_MAX;  // Initialize current and best path costs
    int tempPath[MAXN];  // Array to store the current path
    int visited[MAXN] = { 0 };  // Array to mark visited cities
    int path[MAXN];  // Array to store the best path
    int startCity = start - 'A';  // Convert start city character to index (A=0, B=1, etc.)
    string sPath = "";  // String to store the result path

    visited[startCity] = 1;  // Mark the start city as visited
    tempPath[0] = startCity;  // Start the path with the start city

    // Call the helper function to find the best path
    branchBoundHelp(G, n, startCity, 1, minCost, tmpRes, Res, tempPath, path, visited);

    // Convert the best path (indices) to a string of city characters
    for (int i = 0; i < n; i++) {
        char c = (char)(path[i] + 'A');
        sPath += c;
        if (i != n - 1) {
            sPath += " ";
        }
    }
    sPath += " ";
    sPath += (char)(path[0] + 'A');  // Add the start city at the end to complete the cycle

    return sPath;
}

// Main function to solve the Traveling Salesman Problem
// G: adjacency matrix, n: number of cities, start: starting city character
string Traveling(int G[MAXN][MAXN], int n, char start) {
    // Replace zero costs (no edge) with a very large value (MAXINT)
    // This ensures that paths without direct edges are considered very costly
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && G[i][j] == 0) {
                G[i][j] = MAXINT;
            }
        }
    }
    return branchBound(G, n, start);  // Call the Branch and Bound algorithm
}