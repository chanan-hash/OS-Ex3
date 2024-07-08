#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

/**
 *  This represtent the Kosaraju-Sharir algotirthm for finding CSS in directed graph
 */

/**
 * The first dfs visit.
 * Simple DFS visited on the graph. Starting with the first node continue visiting as DFS works
 */
void DFS_First(vector<vector<int>> &graph, int node, stack<int> &stack, vector<bool> &visited)
{
    visited[node] = true;
    for (int neighbor : graph[node])
    {
        if (!visited[neighbor])
        { // if we haven't visited it, we will go inside and visit. (!false = true)
            DFS_First(graph, neighbor, stack, visited);
        }
    }
    stack.push(node); // the dfs stack
}

/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void DFS(vector<vector<int>>& graph, int node, vector<bool>& visited, vector<int>& finishOrder, bool fillOrder) {
    visited[node] = true;
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[node][i] && !visited[i]) {
            DFS(graph, i, visited, finishOrder, fillOrder);
        }
    }
    if (fillOrder) finishOrder.push_back(node);
}

void fillOrder(vector<vector<int>>& graph, vector<int>& finishOrder, vector<bool>& visited) {
    for (int i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            DFS(graph, i, visited, finishOrder, true);
        }
    }
}

vector<vector<int>> transposeGraph(vector<vector<int>>& graph) {
    vector<vector<int>> transposed(graph.size(), vector<int>(graph.size(), 0));
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            transposed[i][j] = graph[j][i];
        }
    }
    return transposed;
}

void printSCCs(vector<vector<int>>& graph) {
    vector<bool> visited(graph.size(), false);
    vector<int> finishOrder;
    fillOrder(graph, finishOrder, visited);

    vector<vector<int>> transposedGraph = transposeGraph(graph);
    fill(visited.begin(), visited.end(), false);

    reverse(finishOrder.begin(), finishOrder.end()); // Reverse to get correct order

    for (int i : finishOrder) {
        if (!visited[i]) {
            vector<int> component;
            DFS(transposedGraph, i, visited, component, false);
            for (int v : component) cout << v << " ";
            cout << endl;
        }
    }
}

int main() {
    int vertices, edges;
    cin >> vertices >> edges;

    vector<vector<int>> graph(vertices, vector<int>(vertices, 0));
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1; // Assuming 0-based indexing
    }

    printSCCs(graph);

    return 0;
}
*/

/********************Adjancey list *********************** */
/*

#include <iostream>
#include <vector>
#include <stack>
#include <list>
using namespace std;

void DFS_First(vector<list<int>> &graph, int node, stack<int> &stack, vector<bool> &visited) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            DFS_First(graph, neighbor, stack, visited);
        }
    }
    stack.push(node); // Push the node after visiting all its neighbors
}

void DFS_Second(vector<list<int>> &transposeGraph, int node, vector<bool> &visited) {
    cout << node << " ";
    visited[node] = true;
    for (int neighbor : transposeGraph[node]) {
        if (!visited[neighbor]) {
            DFS_Second(transposeGraph, neighbor, visited);
        }
    }
}

vector<list<int>> transposeGraph(vector<list<int>> &graph) {
    vector<list<int>> transposed(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
        for (int neighbor : graph[i]) {
            transposed[neighbor].push_back(i);
        }
    }
    return transposed;
}

void findSCCs(vector<list<int>> &graph) {
    stack<int> stack;
    vector<bool> visited(graph.size(), false);

    // Fill vertices in stack according to their finishing times
    for (int i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            DFS_First(graph, i, stack, visited);
        }
    }

    // Create a transposed graph
    vector<list<int>> transposed = transposeGraph(graph);

    // Mark all vertices as not visited (For second DFS)
    fill(visited.begin(), visited.end(), false);

    // Process all vertices in order defined by Stack
    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();

        if (!visited[v]) {
            DFS_Second(transposed, v, visited);
            cout << endl; // SCC finished
        }
    }
}

int main() {
    int vertices, edges;
    cin >> vertices >> edges;

    vector<list<int>> graph(vertices);
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    findSCCs(graph);

    return 0;
}

*/

int main()
{
    // int vertices;
    // int edges;
    // cin >> vertices;
    // cin >> edges;
    int vertices, edges;
    cin >> vertices >> edges;

    vector<list<int>> graph(vertices); // Using a vector of lists for the adjacency list representation

    for (int i = 0; i < edges; ++i)
    {
        int u, v;
        cin >> u >> v;         // Read each edge
        graph[u].push_back(v); // Add v to u's list to represent a directed edge from u to v
    }
    return 0;
}
