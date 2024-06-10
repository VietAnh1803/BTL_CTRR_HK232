#include <iostream>
#include <memory>
#include "bellman.h"
#include "tsm.h"
using namespace std;
/*Command .\program.exe > output.txt to print result in file output.txt*/
// Function to calculate the distance of a path based on the given adjacency matrix
int pathDistance(string strpath, int G[20][20]) {
    int distance = 0;
    if (strpath.length() == 1)
        return 0;
    for (int i = 0; i < strpath.length() - 2; i++) {
        if (strpath[i] >= 'A' && strpath[i] <= 'Z')
            distance += G[strpath[i] - 'A'][strpath[i + 2] - 'A'];
    }
    return distance;
}
// Function to print the graph for debugging purposes
void printGraph(const int G[20][20]) {
    std::cout << "Graph adjacency matrix:\n";
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            std::cout << G[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    unique_ptr<int[]> BFValue(new int[20]);
    unique_ptr<int[]> BFPrev(new int[20]);
    int G[20][20] = {
        { 52,   0,  15,  72,  61,  21,  83,  87,  75,  75,  88, 100,  24,   3,  22,  53,   2,  88,  30,  38},
        {  2,  64,  60,  21,  33,  76,  58,  22,  89,  49,  91,  59,  42,  92,  60,  80,  15,  62,  62,   0},
        { 62,  51,  55,  64,   3,  51,   7,  21,  73,  39,  18,   4,  89,  60,  14,   9,  90,  53,   2,  84},
        { 92,  60,  71,  44,   8,  47,  35,   0,  81,  36,  50,   4,   2,   6,  54,   4,  54,  93,   0,  18},
        { 90,   0,  34,  74,  62, 100,  14,   0,  48,  15,  72,  78,  87,  62,  40,  85,  80,   0,  53,  24},
        { 26,   0,  60,  41,  29,  15,  45,  65,  89,   0,   9,  88,   1,   8,  88,   0,  11,  81,   0,  35},
        { 35,  33,   5,  41,  28,   7,  73,  72,  12,   0,  33,  48,  23,  62,  88,  37,  99,  44,  86,  91},
        { 35,  65,  99,  47,  78,   3,   1,   5,  90,  14,  27,   9,  79,  15,  90,   0,  77,  51,  63,  96},
        { 52,  96,   4,  94,  23,   0,  43,  29,  36,  13,  32,  71,  59,  86,   0,  66,  42,  45,  62,  57},
        {  0,   0,  28,  44,  84,  30,  62,  75,  92,  89,  62,  97,   1,  27,  62,  77,   3,  70,  72,  27},
        {  9,  62,   0,  97,  51,  44,   0,   0,  59,  32,  96,  88,  52,   0,  58,  52,  12,  39,   0,   3},
        { 56,  81,  59,   2,   2,  92,  54,  87,  96,  97,   1,  19,   2,  53,  44,  90,  32,  70,  32,  68},
        { 55,  75,  56,  17,   0,  24,  69,  98,  70,  86,   0,   0,  97,  73,  59,  70,  80,  93,   3,  20},
        { 59,  36,   0,  90,  67,  19,  20,  96,  71,  52,  33,  40,  39,   0,   1,   0,  92,  57,  89,  50},
        { 23,  31,  94,  42,  99,   7,  16,  90,  60,   2,   1,  48,  12,  69,  37,   0,   9,  99,  19,  48},
        {  0,   3,  20,  24,  54,  33,  24,  75,  72,  36,  38,  84,  99,  89,  99,  25,  93,  18,  82,  66},
        { 54,  35,  80,  61,  41, 100,  33,   0,  33,  14,  21,  48,  20,   8,   7,  67,  17,  33,  48,  76},
        { 59,  86,  22,  30,  38,   0,  54,   8,  27,  27,   0,  21,  30,  97,  28,   0,  97,  69,  61,  48},
        {  0,   4,  35,  64,  49,  17,   0,   0,  30,  93,  46,   6,  99,  37,   0,  93,  46,  53,  95,  99},
        {  0,  97,   0,  85,  32,  87,  33,  67,  18,  25,  95,  54,  58,  67,  46,  24,  32,  47,  86,  23}
    };

    // Example usage of Bellman-Ford and TSP solutions
    cout << "Bellman-Ford Algorithm Result:" << endl;
    for (int i = 0; i < 20; i++) {
        cout << "Step " << i << ": ";
        BF(G, 20, 'A', BFValue.get(), BFPrev.get());
        cout << "BFValue: ";
        for (int z = 0; z < 20; z++) {
            cout << BFValue[z] << " ";
        }
        cout << endl;

        cout << "BFPrev: ";
        for (int z = 0; z < 20; z++) {
            cout << BFPrev[z] << " ";
        }
        cout << endl;
    }

    cout << "Traveling Salesman Problem Result:" << endl;
    string result = Traveling(G, 20, 'A');
    if (result == "No path exists") {
        cout << "Distance of path: -1" << endl;
    } else {
        cout << "Path: " << result << endl;
        cout << "Distance of path: " << pathDistance(result, G) << endl;
    }

    return 0;
}