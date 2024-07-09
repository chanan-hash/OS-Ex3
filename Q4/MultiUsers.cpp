#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

#define PORT "9034" // Port to listen on

vector<list<int>> graph; // global graph for the program

// The kosaraju algorithm to find strongly connected components in a graph
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

// Function for new graph
void createGraph (vector<list<int>> &graph, int vertices, int edges)
{
    graph = vector<list<int>>(vertices + 1);    
    int from, to;
    for (int i = 0; i < edges; i++)
    {
        cin >> from >> to;
        graph[from].push_back(to);
    }
}

void command_handler(string input){
    if(input == "Newgraph\n"){
        int n, m;
        cin >> n >> m;
        createGraph(graph, n, m);
        cout << "Created a new graph with " << n << " vertices and " << m << " edges" << endl;
        fflush(stdout);
    }

    else if(input == "Kosaraju\n"){
        int n;
        cin >> n;
        kosaraju_by_list(graph, n);
    }
    else if (input == "Newedge\n"){
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
        cout << "Added a new edge from " << from << " to " << to << endl;
        fflush(stdout);
    }
    else if (input == "Removeedge\n"){
        int from, to;
        cin >> from >> to;
        graph[from].remove(to);
        cout << "Removed the edge from " << from << " to " << to << endl;
        fflush(stdout);
    }
    else if (input == "Exit\n"){
        cout << "Exiting the program" << endl;
        exit(1);
    }
    else{
        cout << "Invalid command" << endl;
        fflush(stdout);
    }
}
