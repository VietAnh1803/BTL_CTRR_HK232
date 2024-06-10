#include "bellman.h"

// Function to perform the Bellman-Ford algorithm to find the shortest paths from the start vertex
void BF(int G[20][20], int numberOfVertices, char startVertex, int* Label, int* Prev) {
    int V = (int)(startVertex - 'A');
    int* tempValue = new int[numberOfVertices];
    int* tempPrev = new int[numberOfVertices];

    // Initialize the distance to the start vertex as 0
    if (Label[V] == -1) Label[V] = 0;

    // Copy current labels and predecessors
    for (int i = 0; i < numberOfVertices; ++i) {
        tempValue[i] = Label[i];
        tempPrev[i] = Prev[i];
    }

    // Update the labels and predecessors for each vertex
    for (int i = 0; i < numberOfVertices; ++i) {
        if (tempValue[i] == -1) continue;
        for (int j = 0; j < numberOfVertices; ++j) {
            if (G[i][j] != 0 && (Label[j] == -1 || Label[j] > tempValue[i] + G[i][j])) {
                Label[j] = tempValue[i] + G[i][j];
                Prev[j] = i;
            }
        }
    }

    delete[] tempValue;
    delete[] tempPrev;
}

// Function to construct the path from startVertex to goalVertex using the results from the Bellman-Ford algorithm
std::string BF_Path(int G[20][20], int numberOfVertices, char startVertex, char goalVertex) {
    int* Label = new int[numberOfVertices];
    int* Prev = new int[numberOfVertices];

    // Initialize labels and predecessors
    for (int i = 0; i < numberOfVertices; ++i) {
        Label[i] = -1;
        Prev[i] = -1;
    }

    // Perform the Bellman-Ford algorithm numberOfVertices-1 times
    for (int i = 0; i < numberOfVertices - 1; ++i) {
        BF(G, numberOfVertices, startVertex, Label, Prev);
    }

    int goal = (int)(goalVertex - 'A');
    if (Label[goal] == -1) {
        delete[] Label;
        delete[] Prev;
        return "No path exists";
    }

    std::vector<char> path;
    for (int currentVertex = goal; currentVertex != -1; currentVertex = Prev[currentVertex]) {
        path.push_back((char)('A' + currentVertex));
    }

    std::reverse(path.begin(), path.end());
    std::string result;
    for (char vertex : path) {
        result += vertex;
        result += ' ';
    }
    result.pop_back();

    delete[] Label;
    delete[] Prev;
    return result;
}