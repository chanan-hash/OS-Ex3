#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <list>

using namespace std;
/**
 * Kosaraju's Algorithm using deque and list data structures.
 * The first DFS is using the same objects in both ways.
 */

void DFS(vector<vector<int>> &graph, int vertex, vector<bool> &visited, stack<int> &stack)
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

/**
 * The component, will be a list of integers, that will store the vertices of the component.
 */
void DFS_List(vector<vector<int>> &graph, int vertex, vector<bool> &visited, list<int> &component)
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

/**
 * The component, will be a deque of integers, that will store the vertices of the component.
 */
void DFS_Deque(vector<vector<int>> &graph, int vertex, vector<bool> &visited, deque<int> &component)
{
    visited[vertex] = true;
    component.push_back(vertex);
    for (int next_vertex : graph[vertex]) // going over the neighbors of the vertex
    {
        if (!visited[next_vertex])
        {
            DFS_Deque(graph, next_vertex, visited, component);
        }
    }
}

void Kosaraju_by_list(int vertices, vector<vector<int>> &graph)
{
    vector<bool> visited(vertices + 1, false);
    stack<int> stack;

    for (int i = 1; i <= vertices; i++)
    {
        if (!visited[i])
        {
            DFS(graph, i, visited, stack);
        }
    }

    vector<vector<int>> reverse_graph(vertices + 1);
    for (int i = 1; i <= vertices; i++)
    {
        for (int j : graph[i])
        {
            reverse_graph[j].push_back(i);
        }
    }

    fill(visited.begin(), visited.end(), false);

    while (!stack.empty())
    {
        int vertex = stack.top();
        stack.pop();
        if (!visited[vertex])
        {
            list<int> component; // the component will be stored in a list
            DFS_List(reverse_graph, vertex, visited, component);

            for (int vertex : component) // also printing the component
            {
                cout << vertex << " ";
            }
            cout << endl;
        }
    }
}

// works the same as the list but with a deque
void Kosaraju_by_deque(int vertices, vector<vector<int>> &graph)
{
    vector<bool> visited(vertices + 1, false);
    stack<int> stack;

    for (int i = 1; i <= vertices; i++)
    {
        if (!visited[i])
        {
            DFS(graph, i, visited, stack);
        }
    }

    vector<vector<int>> reverse_graph(vertices + 1);
    for (int i = 1; i <= vertices; i++)
    {
        for (int j : graph[i])
        {
            reverse_graph[j].push_back(i);
        }
    }

    fill(visited.begin(), visited.end(), false);

    while (!stack.empty())
    {
        int vertex = stack.top();
        stack.pop();
        if (!visited[vertex])
        {
            deque<int> component; // the component will be stored in a deque
            DFS_Deque(reverse_graph, vertex, visited, component);

            for (int vertex : component) // also printing the component
            {
                cout << vertex << " ";
            }
            cout << endl;
        }
    }
}

int main()
{
    int vertices;
    int num_edges;
    cin >> vertices >> num_edges;

    vector<vector<int>> graph(vertices + 1); // like the adjacency list

    for (int i = 0; i < num_edges; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    cout << "The strongly connected components are, by list: " << endl;
    Kosaraju_by_list(vertices, graph); // calling the function

    cout << "\nThe strongly connected components are, by deque: " << endl;
    Kosaraju_by_deque(vertices, graph); // calling the function

    return 0;
}