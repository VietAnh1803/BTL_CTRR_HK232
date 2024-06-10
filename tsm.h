#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
#include <string>
#include <fstream>
#ifndef TSM_H
#define TSM_H

using namespace std;
const int MAXN = 20; // Maximum number of cities/nodes
const int MAXINT=-1;
extern int DEM;  // Declaration, not definition
extern int COUNT;  // Declaration, not definition

// Function declarations for solving the Traveling Salesman Problem using branch-and-bound
void branchBoundHelp(int G[MAXN][MAXN], int n, int startCity, int i, int minCost, int& tmpRes, int& result, int tempPath[], int path[], int visited[]);
std::string branchBound(int G[MAXN][MAXN], int n, char start);
std::string Traveling(int G[MAXN][MAXN], int n, char start);

#endif