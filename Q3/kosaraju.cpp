#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

// Kosaraju's algorithm to find strongly connected components in a graph
// we will use list for the compenents, and adjacency list for the graph
// after the profiling, we can see that the list is faster than matrix

// here the graph will be represented as a vector of lists - aka adjacency list
void DFS(vector<list<int>> &graph, int vertex, vector<bool> &visited, stack<int> &stack)
{
    visited[vertex] = true;
    for (int i : graph[vertex])
    {
        if (!visited[i])
        {
            DFS(graph, i, visited, stack);
        }
    }
    stack.push(vertex);
}

// after the previous part will use the list to store the components more efficiently
void DFS_List(vector<list<int>> &graph, int vertex, vector<bool> &visited, list<int> &component)
{
    visited[vertex] = true;
    component.push_back(vertex);
    for (int i : graph[vertex])
    {
        if (!visited[i])
        {
            DFS_List(graph, i, visited, component);
        }
    }
}

void kosaraju_by_list(vector<list<int>> &graph, int vertices)
{
    stack<int> stack;
    vector<bool> visited(vertices + 1, false);

    // first DFS to fill the stack
    for (int i = 1; i <= vertices; i++)
    {
        if (!visited[i])
        {
            DFS(graph, i, visited, stack);
        }
    }

    // reverse the graph
    vector<list<int>> reverse_graph(vertices + 1);
    for (int i = 1; i <= vertices; i++)
    {
        for (int j : graph[i])
        {
            reverse_graph[j].push_back(i);
        }
    }

    // reset the visited array
    fill(visited.begin(), visited.end(), false);

    // second DFS to get the components
    while (!stack.empty())
    {
        int vertex = stack.top();
        stack.pop();
        if (!visited[vertex])
        {
            list<int> component;
            DFS_List(reverse_graph, vertex, visited, component);
            for (int i : component)
            {
                cout << i << " ";
            }
            cout << endl;
        }
    }
}

int main()
{
    string input;

    int vertices = 0, edges = 0;

    vector<list<int>> graph;

    while (cin >> input)
    {
        if (input == "Newgraph")
        {
            cin >> vertices;
            cin >> edges;
            graph = vector<list<int>>(vertices + 1);

            for (int i = 0; i < edges; i++)
            {
                int from, to;
                cin >> from >> to;
                graph[from].push_back(to);
            }
        }
        else if (input == "Kosaraju")
        {
            kosaraju_by_list(graph, vertices);
        }
        else if (input == "Newedge")
        {
            int i, j;
            cin >> i >> j;
            graph[i].push_back(j);
        }
        else if (input == "Removeedge")
        {
            int i, j;
            cin >> i >> j;
            graph[i].remove(j);
        }
        else
        {
            cout << "Invalid input" << endl;
        }
    }
    return 0;
}
