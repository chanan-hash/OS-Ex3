#include <iostream>
#include <poll.h>
#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <list>
#include <string>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>

#include "Reactor.hpp"
using namespace std;

reactor r;
vector<list<int>> graph;

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
void createGraph(vector<list<int>> &graph, int vertices, int edges)
{
    graph = vector<list<int>>(vertices + 1);
    int from, to;
    for (int i = 0; i < edges; i++)
    {
        cin >> from >> to;
        graph[from].push_back(to);
    }
}

void command_handler(string input)
{
    if (input == "Newgraph\n")
    {
        int n, m;
        cin >> n >> m;
        createGraph(graph, n, m);
        cout << "Created a new graph with " << n << " vertices and " << m << " edges" << endl;
        fflush(stdout);
    }

    else if (input == "Kosaraju\n")
    {
        int n = graph.size() - 1;
        kosaraju_by_list(graph, n);
    }
    else if (input == "Newedge\n")
    {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
        cout << "Added a new edge from " << from << " to " << to << endl;
        fflush(stdout);
    }
    else if (input == "Removeedge\n")
    {
        int from, to;
        cin >> from >> to;
        graph[from].remove(to);
        cout << "Removed the edge from " << from << " to " << to << endl;
        fflush(stdout);
    }
    else if (input == "Exit\n")
    {
        cout << "Exiting the program" << endl;
        exit(1);
    }
    else
    {
        cout << "Invalid command" << endl;
        fflush(stdout);
    }
}

void *client_handler(int fd)
{
    char buffer[1024];
    int n = read(fd, buffer, 1024);
    if (n < 0)
    {
        cerr << "Error reading from socket" << endl;
        exit(1);
    }
    string input(buffer);
    command_handler(input);
    return nullptr;
}

int get_listener_socket(void)
{
    int listener; // Listening socket descriptor
    int yes = 1;  // For setsockopt() SO_REUSEADDR, below
    int rv;

    struct addrinfo hints, *ai, *p;

    // Get us a socket and bind it
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0)
    {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = ai; p != NULL; p = p->ai_next)
    {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0)
        {
            continue;
        }

        // Lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(listener);
            continue;
        }

        break;
    }

    freeaddrinfo(ai); // All done with this

    // If we got here, it means we didn't get bound
    if (p == NULL)
    {
        return -1;
    }

    // Listen
    if (listen(listener, 10) == -1)
    {
        return -1;
    }

    return listener;
}

void *listner_handler(int fd)
{

    // int new_fd = accept(fd, NULL, NULL);

    // r.addFdToReactor(new_fd, client_handler);

    // return nullptr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int new_fd = accept(fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (new_fd == -1)
    {
        cerr << "Error accepting connection" << endl;
        exit(1);
    }
    r.addFdToReactor(new_fd, client_handler);
    return nullptr;
}

int main()
{

    int fd = get_listener_socket();

    r.addFdToReactor(fd, listner_handler);

    r.startReactor();
    
    return 0;
}