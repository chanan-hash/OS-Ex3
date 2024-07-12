// #include <iostream>
// #include <list>
// #include <vector>
// using namespace std;

// void DFS(int v, vector<bool> &visited, const vector<list<int>> &graph)
// {
//     visited[(size_t)v] = true;
//     for (int adj : graph[(size_t)v])
//     {
//         if (!visited[(size_t)adj])
//         {
//             DFS(adj, visited, graph);
//         }
//     }
// }

// bool isConnected(const vector<list<int>> &graph, int &startNode)
// {
//     vector<bool> visited(graph.size(), false);
//     int nonZeroDegreeCount = 0;
//     for (int i = 0; i < graph.size(); i++)
//     {
//         if (graph[(size_t)i].size() > 0)
//         {
//             startNode = i; // Find a vertex with non-zero degree
//             nonZeroDegreeCount++;
//         }
//     }
//     if (nonZeroDegreeCount == 0)
//         return true; // Eulerian cycle exists in an empty graph
//     DFS(startNode, visited, graph);
//     for (int i = 0; i < graph.size(); i++)
//     {
//         if (visited[(size_t)i] == false && graph[(size_t)i].size() > 0)
//             return false; // Graph is not connected
//     }
//     return true;
// }

// bool isEulerianCycle(const vector<list<int>> &graph)
// {
//     int startNode = -1;
//     if (!isConnected(graph, startNode))
//         return false; // Check if graph is connected
//     for (int i = 0; i < graph.size(); i++)
//     {
//         if (graph[(size_t)i].size() & 1)
//             return false; // Check if all vertices have even degree
//     }
//     return true; // Graph has an Eulerian cycle
// }

// int main()
// {
//     // Example graph
//     vector<list<int>> graph = {
//         {1, 2, 3},
//         {0, 2},
//         {0, 1, 3},
//         {0, 2}};

//     if (isEulerianCycle(graph))
//     {
//         cout << "The graph has an Eulerian cycle." << endl;
//     }
//     else
//     {
//         cout << "The graph does not have an Eulerian cycle." << endl;
//     }

//     // Graph g1
//     vector<list<int>> g1 = {
//         {2, 3}, // Vertex 0 is connected to vertices 2 and 3
//         {0},    // Vertex 1 is connected to vertex 0
//         {1},    // Vertex 2 is connected to vertex 1
//         {4},    // Vertex 3 is connected to vertex 4
//         {}      // Vertex 4 has no outgoing edges
//     };

//     if (isEulerianCycle(g1))
//     {
//         cout << "The graph has an Eulerian cycle." << endl;
//     }
//     else
//     {
//         cout << "The graph does not have an Eulerian cycle." << endl;
//     }

//     // Graph g2
//     vector<list<int>> g2 = {
//         {2, 3, 4}, // Vertex 0 is connected to vertices 2, 3, and 4
//         {0},       // Vertex 1 is connected to vertex 0
//         {1},       // Vertex 2 is connected to vertex 1
//         {4},       // Vertex 3 is connected to vertex 4
//         {0}        // Vertex 4 is connected back to vertex 0
//     };

//     if (isEulerianCycle(g2))
//     {
//         cout << "The graph has an Eulerian cycle." << endl;
//     }
//     else
//     {
//         cout << "The graph does not have an Eulerian cycle." << endl;
//     }

//     // Graph g3
//     vector<list<int>> g3 = {
//         {2, 3}, // Vertex 0 is connected to vertices 2 and 3
//         {0, 3}, // Vertex 1 is connected to vertices 0 and 3
//         {1},    // Vertex 2 is connected to vertex 1
//         {4},    // Vertex 3 is connected to vertex 4
//         {}      // Vertex 4 has no outgoing edges
//     };

//     if (isEulerianCycle(g3))
//     {
//         cout << "The graph has an Eulerian cycle." << endl;
//     }
//     else
//     {
//         cout << "The graph does not have an Eulerian cycle." << endl;
//     }

//     // Graph g4
//     vector<list<int>> g4 = {
//         {1}, // Vertex 0 is connected to vertex 1
//         {2}, // Vertex 1 is connected to vertex 2
//         {0}  // Vertex 2 is connected back to vertex 0
//     };

//     if (isEulerianCycle(g4))
//     {
//         cout << "The graph has an Eulerian cycle." << endl;
//     }
//     else
//     {
//         cout << "The graph does not have an Eulerian cycle." << endl;
//     }

//     // Graph g5
//     vector<list<int>> g5 = {
//         {}, // Vertex 0 has no outgoing edges
//         {}, // Vertex 1 has no outgoing edges
//         {}  // Vertex 2 has no outgoing edges
//     };

//     if (isEulerianCycle(g5))
//     {
//         cout << "The graph has an Eulerian cycle." << endl;
//     }
//     else
//     {
//         cout << "The graph does not have an Eulerian cycle." << endl;
//     }

//     return 0;
// }

// A C++ program to check if a given graph is Eulerian or not
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <unistd.h> // For getopt

using namespace std;

// A class that represents an undirected graph
class Graph
{
public:
    int V; // Number of vertices
    vector<list<int>> adj; // Vector of adjacency lists

    explicit Graph(int V) : V(V), adj((size_t)V) {
        // The vector is automatically initialized with V elements.
        // Each element is a std::list<int>, initially empty.
    }
    // function to add an edge to graph
    void addEdge(int v, int w);

    // Method to check if this graph is Eulerian or not
    int isEulerian();

    // Method to check if all non-zero degree vertices are connected
    bool isConnected();

    // Function to do DFS starting from v. Used in isConnected();
    void DFSUtil(int v, bool visited[]);
};

void Graph::addEdge(int v, int w)
{
    adj[(size_t)v].push_back(w);
    adj[(size_t)w].push_back(v); // Note: the graph is undirected
}

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[(size_t)v].begin(); i != adj[(size_t)v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// Method to check if all non-zero degree vertices are connected.
// It mainly does DFS traversal starting from
bool Graph::isConnected()
{
    // Mark all the vertices as not visited
    bool visited[(size_t)V];
    int i;
    for (i = 0; i < V; i++)
        visited[i] = false;

    // Find a vertex with non-zero degree
    for (i = 0; i < V; i++)
        if (adj[(size_t)i].size() != 0)
            break;

    // If there are no edges in the graph, return true
    if (i == V)
        return true;

    // Start DFS traversal from a vertex with non-zero degree
    DFSUtil(i, visited);

    // Check if all non-zero degree vertices are visited
    for (i = 0; i < V; i++)
        if (visited[i] == false && adj[(size_t)i].size() > 0)
            return false;

    return true;
}

/* The function returns one of the following values
0 --> If graph is not Eulerian
1 --> If graph has an Euler path (Semi-Eulerian)
2 --> If graph has an Euler Circuit (Eulerian) */
int Graph::isEulerian()
{
    // Check if all non-zero degree vertices are connected
    if (isConnected() == false)
        return 0;

    // Count vertices with odd degree
    int odd = 0;
    for (int i = 0; i < V; i++)
        if (adj[(size_t)i].size() & 1)
            odd++;

    // If count is more than 2, then graph is not Eulerian
    if (odd > 2)
        return 0;

    // If odd count is 2, then semi-eulerian.
    // If odd count is 0, then eulerian
    // Note that odd count can never be 1 for undirected graph
    return (odd) ? 1 : 2;
}

// Function to run test cases
void test(Graph &g)
{
    int res = g.isEulerian();
    if (res == 0)
        cout << "graph is not Eulerian\n";
    else if (res == 1)
        cout << "graph has a Euler path\n";
    else
        cout << "graph has a Euler cycle\n";
}

// Driver program to test above function
// int main()
// {
//     // Let us create and test graphs shown in above figures
//     Graph g1(5);
//     g1.addEdge(1, 0);
//     g1.addEdge(0, 2);
//     g1.addEdge(2, 1);
//     g1.addEdge(0, 3);
//     g1.addEdge(3, 4);
//     test(g1);

//     Graph g2(5);
//     g2.addEdge(1, 0);
//     g2.addEdge(0, 2);
//     g2.addEdge(2, 1);
//     g2.addEdge(0, 3);
//     g2.addEdge(3, 4);
//     g2.addEdge(4, 0);
//     test(g2);

//     Graph g3(5);
//     g3.addEdge(1, 0);
//     g3.addEdge(0, 2);
//     g3.addEdge(2, 1);
//     g3.addEdge(0, 3);
//     g3.addEdge(3, 4);
//     g3.addEdge(1, 3);
//     test(g3);

//     // Let us create a graph with 3 vertices
//     // connected in the form of cycle
//     Graph g4(3);
//     g4.addEdge(0, 1);
//     g4.addEdge(1, 2);
//     g4.addEdge(2, 0);
//     test(g4);

//     // Let us create a graph with all vertices
//     // with zero degree
//     Graph g5(3);
//     test(g5);

//     return 0;
// }

// Function to generate a random graph
void generateRandomGraph(Graph &graph, int V, int E)
{
    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < E; ++i)
    {
        int u = rand() % V;
        int v = rand() % V;
        graph.addEdge(u, v);
        // For undirected graph, add the edge in the opposite direction as well
        // graph.addEdge(v, u);
    }
}

int main(int argc, char *argv[])
{
    int V = 0;    // Number of vertices
    int E = 0;    // Number of edges
    int seed = 0; // Random seed
    int opt;

    // Parse command line arguments
    while ((opt = getopt(argc, argv, "v:e:s:")) != -1)
    {
        switch (opt)
        {
        case 'v':
            V = atoi(optarg);
            break;
        case 'e':
            E = atoi(optarg);
            break;
        case 's':
            seed = atoi(optarg);
            srand((unsigned int)seed); // Seed the random number generator
            break;
        default: /* '?' */
            cerr << "Usage: " << argv[0] << " -v num_vertices -e num_edges -s seed" << endl;
            exit(EXIT_FAILURE);
        }
    }

    if (V <= 0 || E < 0)
    {
        cerr << "Invalid number of vertices or edges." << endl;
        exit(EXIT_FAILURE);
    }

    // Create a graph with V vertices
    Graph g(V);

    // Generate a random graph
    generateRandomGraph(g, V, E);

    // Run the Euler circle test algorithm on the generated graph
    test(g);

    return 0;
}