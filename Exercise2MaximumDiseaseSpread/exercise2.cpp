#include <iostream>
#include <vector>
#include <stack>

using namespace std;

enum class Color { WHITE, GREY, BLACK };

void addAdjVertices(vector<vector<int>>& adjList, int u, int v) {
    adjList[u].push_back(v);
}

void iterativeDFS(vector<vector<int>>& adjacencyList, int startV, stack<int>& inverseStack, int size) {
    vector<Color> Vcolors(size, Color::WHITE);
    stack<int> DFS_stack;
    
    for (int i = 0; i < size; i++) {
        if (Vcolors[i] == Color::WHITE) {
            DFS_stack.push(i);

            while (!DFS_stack.empty()) {
                int current = DFS_stack.top();
                DFS_stack.pop();

                if (Vcolors[current] == Color::WHITE) {
                    DFS_stack.push(current);
                    Vcolors[current] = Color::GREY;

                    for (int adjVertices : adjacencyList[current]) {
                        if (Vcolors[adjVertices] == Color::WHITE) {
                            DFS_stack.push(adjVertices);
                        }
                    }
                } else if (Vcolors[current] == Color::GREY) {
                    inverseStack.push(current);
                    Vcolors[current] = Color::BLACK;
                }
            }
        }
    }
}

int findSCCs(vector<vector<int>>& transposeGraph, stack<int>& inverseStack, int size) {
   
    vector<Color> Vcolors(size, Color::WHITE);
    vector<int> jumps(size, 0);
    int maxJumps = 0;

    while (!inverseStack.empty()) {
        int vertex = inverseStack.top();
        inverseStack.pop();

        if (Vcolors[vertex] == Color::WHITE) {
            stack<int> greyVerts;
            stack<int> SCCStack;
            SCCStack.push(vertex);

            int SCCJumpValue = 0;
            while (!SCCStack.empty()) {
                int current = SCCStack.top();
                SCCStack.pop();
                Vcolors[current] = Color::GREY;
                greyVerts.push(current);
                for (int adjVertices : transposeGraph[current]) {
    
                    if (Vcolors[adjVertices] == Color::WHITE) {
                        SCCStack.push(adjVertices);
                        jumps[adjVertices] = SCCJumpValue;
                    }
                    else if (Vcolors[adjVertices] == Color::BLACK){
                        if (jumps[adjVertices] >= jumps[current]) {
                            jumps[current] = jumps[adjVertices] + 1;
                            SCCJumpValue = std::max(jumps[current], SCCJumpValue);
                        }
                    }
                }
            }
            while (!greyVerts.empty()) {
                    int greyVert = greyVerts.top();
                    greyVerts.pop();
                    jumps[greyVert] = SCCJumpValue;
                    Vcolors[greyVert] = Color::BLACK;
            }
            maxJumps = std::max(maxJumps, SCCJumpValue);
        }
    }
    return maxJumps;
}

int main() {
    int V, S, u, v;
    stack<int> inverseStack;

    scanf("%d %d", &V, &S);
    vector<vector<int>> adjacencyList(V);
    vector<vector<int>> transposeGraph(V);

    for (int i = 0; i < S; i++) {
        scanf("%d %d", &u, &v);
        addAdjVertices(adjacencyList, u - 1, v - 1);    // indexes from 0 to V-1
        addAdjVertices(transposeGraph, v - 1, u - 1);   // indexes from 0 to V-1
    }
    iterativeDFS(adjacencyList, 0, inverseStack, V);
    printf("%d\n", findSCCs(transposeGraph, inverseStack, V));

    return 0;
}