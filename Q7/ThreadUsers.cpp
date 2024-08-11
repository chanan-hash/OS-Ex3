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

using namespace std;

#define PORT "9031" // Port to listen on

vector<list<int>> graph; // global graph for the program

mutex mtx;

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

void client_handler(int fd)
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
}

// Function to handle the client for IPV4 or IPV6
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main()
{
    // beej's code for poll

    int listener;                       // listening socket descriptor
    int newfd;                          // newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;

    string ans;

    char remoteIP[INET6_ADDRSTRLEN];

    int yes = 1; // for setsockopt() SO_REUSEADDR, below
    int rv;

    struct addrinfo hints, *ai, *p;

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
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0)
        {
            continue;
        }

        // allow socket descriptor to be reuseable
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(listener);
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
    if (listen(listener, 10) == -1) // max clinets 10
    {
        perror("listen");
        exit(3);
    }

    cout << "Waiting for connections..." << endl;
    addrlen = sizeof(remoteaddr);
    for (;;)
    { // forever

        newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);

        if (newfd == -1)
        {
            perror("accept");
            continue;
        }

        const char *ipclient = inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr *)&remoteaddr), remoteIP, INET6_ADDRSTRLEN);
        cout << "Accepted connection from " << ipclient << endl;

        // create a thread for each client
        cout << "Number of threads: " << thread::hardware_concurrency() << endl;

        thread t(client_handler, newfd);

        t.detach();
    }

    return 0;
}