#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <list>

using namespace std;

void DFS(vector<vector<int>> &graph, int vertex, vector<bool> &visited, stack<int> &stack)
{
    visited[vertex] = true;
    for (size_t i = 0; i < graph[vertex].size(); i++)
    {
        if (!visited[i] && graph[vertex][i]) // The diganol is not considered, because it supposed to be 0
        {
            DFS(graph, i, visited, stack);
        }
    }
    stack.push(vertex);
}

void DFS_List(vector<vector<int>> &graph, int vertex, vector<bool> &visited, list<int> &component)
{
    visited[vertex] = true;
    component.push_back(vertex);
    for (size_t i = 0; i < graph[vertex].size(); i++)
    {
        if (!visited[i] && graph[vertex][i])
        {
            DFS_List(graph, i, visited, component);
        }
    }
}

void kosaraju_by_matrix(vector<vector<int>> &graph, int vertices)
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
    vector<vector<int>> reverse_graph(vertices + 1, vector<int>(vertices + 1, 0));

    for (int i = 1; i <= vertices; i++)
    {
        for (int j = 1; j <= vertices; j++)
        {
            if (graph[i][j])
            {
                reverse_graph[j][i] = 1;
            }
        }
    }

    // second DFS to find the components
    fill(visited.begin(), visited.end(), false);
    while (!stack.empty())
    {
        int vertex = stack.top();
        stack.pop();
        if (!visited[vertex])
        {
            list<int> component;
            DFS_List(reverse_graph, vertex, visited, component);
            cout << "Component: ";
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
    int vertices, edges;
    cin >> vertices >> edges;

    vector<vector<int>> graph(vertices + 1, vector<int>(vertices + 1, 0));
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
    }

    kosaraju_by_matrix(graph, vertices);

    return 0;
}
