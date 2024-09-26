#include <iostream>
#include <vector>
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
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable> //For Q10
#include "Proactor.hpp"

using namespace std;

#define PORT "9031" // Port to listen on

vector<list<int>> graph; // global graph for the program

mutex mtx;

// For Q10
condition_variable more_than_50;
bool more_than_50_flag = false;

void kosaraju_status(mutex &mtx)
{
    unique_lock<mutex> lock(mtx); // lock the mutex
    more_than_50.wait(lock, []
                      { return more_than_50_flag; });
    while (true)
    {
        if (more_than_50_flag)
        { // printint in green if the condition is true
            cout << "\033[1;32m" << "50% of the graph in the same scc\n\n"
                 << "\033[0m";
        }
        else
        { // printing in red if the condition is false
            cout << "\033[1;31m" << "Less than 50% of the graph in the same scc\n\n"
                 << "\033[0m";
        }
        more_than_50.wait(lock);
    }
}

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
                // For Q10
                if (component.size() > static_cast<size_t>(vertices / 2))
                {
                    more_than_50_flag = true;
                    more_than_50.notify_one();
                }
                else
                {
                    more_than_50_flag = false;
                    more_than_50.notify_one();
                }
                cout << i << " ";
            }
            cout << endl;
        }
    }
}

// Function for new graph
void createGraph(vector<list<int>> &graph, int vertices, int edges, istringstream &inputbufer, int fd)
{
    graph = vector<list<int>>(vertices + 1);
    int from, to;
    for (int i = 0; i < edges; i++)
    {
        string input;
        char buffer[1024];
        inputbufer >> input;

        string sfrom, sto;
        if (!(inputbufer >> sfrom >> sto))
        {
            int nb = read(fd, buffer, 1024);
            if (nb < 0)
            {
                cerr << "Error reading from socket" << endl;
                exit(1);
            }
            buffer[nb] = '\0';
            inputbufer = istringstream(buffer);
            inputbufer >> sfrom >> sto;
        }
        from = stoi(sfrom);
        to = stoi(sto);

        graph[from].push_back(to);
    }
}

// Adding here mutex to handle the lock
void command_handler(istringstream &inputbufer, int fd)
{
    string input;
    char buffer[1024];
    inputbufer >> input;
    cout << "Received command: " << input << endl;
    // cout << int(input[8]) << endl;
    if (input == "Newgraph")
    {
        string sn, sm;
        if (!(inputbufer >> sn >> sm))
        {
            int nb = read(fd, buffer, 1024);
            if (nb < 0)
            {
                cerr << "Error reading from socket" << endl;
                exit(1);
            }
            buffer[nb] = '\0';
            inputbufer = istringstream(buffer);
            inputbufer >> sn >> sm;
        }
        int n = stoi(sn);
        int m = stoi(sm);

        createGraph(graph, n, m, inputbufer, fd);
        cout << "Created a new graph with " << n << " vertices and " << m << " edges" << endl;
        fflush(stdout);
    }

    else if (input == "Kosaraju")
    {
        int n = graph.size() - 1;
        kosaraju_by_list(graph, n);
    }
    else if (input == "Newedge")
    {
        string sfrom, sto;
        if (!(inputbufer >> sfrom >> sto))
        {
            int nb = read(fd, buffer, 1024);
            if (nb < 0)
            {
                cerr << "Error reading from socket" << endl;
                exit(1);
            }
            buffer[nb] = '\0';
            inputbufer = istringstream(buffer);
            inputbufer >> sfrom >> sto;
        }

        int from, to;

        from = stoi(sfrom);
        to = stoi(sto);

        graph[from].push_back(to);
        cout << "Added a new edge from " << from << " to " << to << endl;
        fflush(stdout);
    }
    else if (input == "Removeedge")
    {
        string sfrom, sto;
        if (!(inputbufer >> sfrom >> sto))
        {
            int nb = read(fd, buffer, 1024);
            if (nb < 0)
            {
                cerr << "Error reading from socket" << endl;
                exit(1);
            }
            buffer[nb] = '\0';
            inputbufer = istringstream(buffer);
            inputbufer >> sfrom >> sto;
        }

        int from, to;
        from = stoi(sfrom);
        to = stoi(sto);
        graph[from].remove(to);
        cout << "Removed the edge from " << from << " to " << to << endl;
        fflush(stdout);
    }
    else if (input == "Exit")
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

void *client_handler(int fd, mutex &mtx)
{
    char buffer[1024];
    int nb;
    while ((nb = read(fd, buffer, 1024)) > 0)
    {
        buffer[nb] = '\0';

        mtx.lock();
        cout << "mutex locked" << endl;

        istringstream inputbufer(buffer);
        command_handler(inputbufer, fd);

        mtx.unlock();
        cout << "mutex unlocked" << endl;
    }
    close(fd);
    cout << "Connection closed" << endl;
    return nullptr; // Adjust this return value as needed
}

int get_listener_fd()
{
    int listener_fd;
    int yes = 1; // for setsockopt() SO_REUSEADDR, below
    struct addrinfo hints, *ai, *p;
    int rv;

    // get us a socket and bind it
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0)
    {
        cerr << "selectserver: " << gai_strerror(rv) << endl;
        exit(1);
    }

    for (p = ai; p != NULL; p = p->ai_next)
    {
        listener_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener_fd < 0)
        {
            continue;
        }

        // allow socket descriptor to be reuseable
        setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener_fd, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(listener_fd);
            continue;
        }

        break;
    }

    // if we got here, it means we didn't get bound
    if (p == NULL)
    {
        cerr << "selectserver: failed to bind\n";
        exit(2);
    }

    freeaddrinfo(ai); // all done with this

    // listen
    if (listen(listener_fd, 10) == -1)
    {
        perror("listen");
        exit(3);
    }

    cout << "server is waiting for connections on port " << PORT << endl;

    return listener_fd;
}

int main()
{
    int listener_fd = get_listener_fd();
    Proactor proactor;

    // For Q10 Kosaraju thread, need to put the detach and the line before in a comment

    // create a theread that will print the status of the kosaraju (just when the condition variable is notified)
    thread kosaraju_thread(kosaraju_status, ref(proactor.get_lock()));
 
    // thread kosaraju_thread(kosaraju_status, ref(mtx));
    // kosaraju_thread.detach();

    proactor.startProactor(listener_fd, bind(client_handler, placeholders::_1, ref(mtx)));
    return 0;
}