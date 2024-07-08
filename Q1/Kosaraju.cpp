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

/**
 * The second dfs visit.
 * This is the second DFS visit. We will visit the nodes in the reverse order of the first DFS visit.
 * That will give us the strongly connected components.
 */
void DFS_Second_Reversed(const vector<vector<int>> &graph, int node, vector<bool> &visited, vector<int>& component)
{
    visited[node] = true;
    component.push_back(node);
    for (int neighbor : graph[node])
    {
        if (!visited[neighbor])
        {
            DFS_Second_Reversed(graph, neighbor, visited, component);
        }
    }
}

/**
 * The main function for the Kosaraju-Sharir algorithm.
 * This function will return the strongly connected components of the graph.
 */

vector<vector<int>> kosaraju_sharir(int vertices, vector<pair<int ,int >> &edges)
{
    vector<vector<int>> graph(vertices + 1); // +1 because the vertices are 1-indexed
    vector<vector<int>> reversed_graph(vertices + 1);
    vector<vector<int>> strongly_connected_components; //each vector is a strongly connected component

    // The auto is used to automatically detect the type of the variable
    for (auto edge : edges)
    {   
        // creating the revers graph by reversing the edges
        graph[edge.first].push_back(edge.second);
        reversed_graph[edge.second].push_back(edge.first);
    }

    stack<int> stack;
    vector<bool> visited(vertices + 1, false);

    for (int i = 1; i <= vertices; i++)
    {
        if (!visited[i])
        {
            DFS_First(graph, i, stack, visited);
        }
    }

    fill(visited.begin(), visited.end(), false);

    while (!stack.empty())
    {
        int node = stack.top();
        stack.pop();
        if (!visited[node])
        {
            vector<int> component;
            DFS_Second_Reversed(reversed_graph, node, visited, component); // this will fill the component vector
            strongly_connected_components.push_back(component);
        }
    }

    return strongly_connected_components;
}

int main()
{
    int vertices, num_edges;
    cin >> vertices >> num_edges;

    vector<pair<int, int>> edges;
    for (int i = 0; i < num_edges; i++)
    {
        int from, to;
        cin >> from >> to;
        edges.emplace_back(from, to);
    }

    vector<vector<int>> strongly_connected_components = kosaraju_sharir(vertices, edges);
 
    cout << "The strongly connected components are: " << endl;
 
    for (vector<int> component : strongly_connected_components)
    {
        for (int node : component)
        {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}