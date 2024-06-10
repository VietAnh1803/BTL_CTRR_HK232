#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function declarations for Bellman-Ford algorithm
void BF(int G[20][20], int numberOfVertices, char startVertex, int* Label, int* Prev);
std::string BF_Path(int G[20][20], int numberOfVertices, char startVertex, char goalVertex);