#include <iostream>
#include <list>
#include <queue>
#include <iterator>
#include <limits>
#include <vector>

using namespace std;

class Vertex 
{
    //Container for information needed for Dijkstra's algorithm
    public:
        //Can be marked as visited or known
        bool visited;
        bool known;

        //Keep track of node distance and number
        int distance;
        int num;

        //Can be chained in a linked list
        Vertex* prev;

        Vertex() : visited(false), distance(-1){};
        Vertex(int adj_vertex, int adj_dist) : visited(false), 
                                                distance(adj_dist),
                                                num(adj_vertex){};
       ~Vertex(){};
};

//A wrapper for a Vertex comparison function
struct BySmallest
{
    //Accept vertex pointers and compare distance values
    bool operator() (Vertex* const& lhs, Vertex* const& rhs) const
    {
        return lhs->distance > rhs->distance;
    }
};

Vertex* run_dijkstras(list<Vertex*>* adj_list, int start_node)
{
    //Run Dijkstra's Algorithm from a given node given an adjacency 
    //list

    //These will record the state of each node and will be joined in
    //a linked list of the shortest path between them
    Vertex* visited = new Vertex[8]();

    //Create a min-heap for Vectors comparing them by distance using
    //the function contained in the wrapper
    priority_queue<Vertex*, vector<Vertex*>, BySmallest> to_visit;

    //Set the starting Vertex's distance to 0 in the visited array.
    visited[start_node].distance = 0;
    visited[start_node].num = start_node;

    //Push the starting Vertex from the array to the min-heap
    to_visit.push(&visited[start_node]);

    while(! to_visit.empty())
    {
        //Get information from the closest Vertex
        Vertex* node = to_visit.top();
        int at_node =  to_visit.top()->num;
        int distance = to_visit.top()->distance;
        to_visit.pop();

        //Mark it as known
        visited[at_node].known = true;

        list<Vertex*>::iterator it;
        
        //Loop through all vertices adjacent to the current Vertex
        for(it = adj_list[at_node].begin();
             it != adj_list[at_node].end(); it++)

             //If the adjacent Vertex is unknown
            if(visited[(*it)->num].known != true)
            {
                int curr_dist = visited[(*it)->num].distance;
                int new_dist = visited[at_node].distance + (*it)->distance;

                visited[(*it)->num].num = (*it)->num;
                
                //Compare the distance of any previous paths
                //to the adjacent Vertex to the distance of the current path 
                if(curr_dist == -1 || curr_dist > new_dist)
                {
                    //Update if first path to Vertexor shorter path
                    visited[(*it)->num].prev = node;
                    visited[(*it)->num].distance = new_dist;
                }

                //If the node has never been visited before, 
                //add to min heap
                if(visited[(*it)->num].visited != true)
                {
                    visited[(*it)->num].visited = true;
                    to_visit.push(&visited[(*it)->num]);
                }
            }
    }

    return visited;
}

void add_to_list(list<Vertex*>* adj_list, int vertex,
                    int adj_vertex, int adj_dist)
{
    //Simplifies creating the adjacency list
    Vertex* new_vert = new Vertex(adj_vertex, adj_dist);
    adj_list[vertex].push_back(new_vert);
}

list<Vertex*>* build_adj_list()
{
    //Build a static adjacency list
    list<Vertex*>* adj_list = new list<Vertex*>[8]();
    
    add_to_list(adj_list, 0, 2, 8);
    add_to_list(adj_list, 0, 3, 6);
    add_to_list(adj_list, 0, 4, 5);

    add_to_list(adj_list, 1, 2, 2);
    add_to_list(adj_list, 1, 5, 2);

    add_to_list(adj_list, 2, 0, 8);
    add_to_list(adj_list, 2, 1, 2);
    add_to_list(adj_list, 2, 5, 7);

    add_to_list(adj_list, 3, 0, 6);
    add_to_list(adj_list, 3, 5, 9);

    add_to_list(adj_list, 4, 0, 5);
    
    add_to_list(adj_list, 5, 1, 2);
    add_to_list(adj_list, 5, 2, 7);
    add_to_list(adj_list, 5, 3, 9);
    add_to_list(adj_list, 5, 6, 6);
    
    add_to_list(adj_list, 6, 5, 6);
    add_to_list(adj_list, 6, 7, 3);
    
    add_to_list(adj_list, 7, 6, 3);
    
    return adj_list;
}

// void print_list(list<Vertex*> adj_list_node)
// {
//     list<Vertex*>::iterator it;

//     for(it = adj_list_node.begin(); it != adj_list_node.end(); it++)
//         cout << "Dist: " << (*it)->distance << endl;
    
// }

// void print_all(list<Vertex*>* adj_list)
// {
//     for(int i = 0; i < 8; i++)
//     {
//         print_list(adj_list[i]);
//         cout << endl;
//     }
// }

int get_input(int num_nodes, int op)
{
    //Get user input for the starting or ending Vertex
    int inpt = -1;

    if(op == 0)
        cout << "Choosing a starting node between 0 and " << num_nodes - 1 << endl;
    else
        cout << "Choosing a ending node between 0 and " << num_nodes - 1 << endl;
    
    cout << ">>> ";

    while(! (cin >> inpt) || inpt < 0 || inpt >= num_nodes)
    {
        if(op == 0)
            cout << "Choosing a starting node between 0 and " << num_nodes - 1 << endl;
        else
            cout << "Choosing a ending node between 0 and " << num_nodes - 1 << endl;
    
        cout << ">>> ";

        //Clear old input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return inpt;
}

void traverse_tree(int end_node, int start_node, Vertex* result)
{
    //Iterate over the path created by the algorithm
    cout << endl;
    cout << "Shortest Path Between " << end_node << " and " 
            << start_node << endl;

    Vertex* curr = &result[end_node];
    
    while(curr && curr->prev)
    {
        cout << curr->num << " -- ";
        curr = curr->prev;
    }

    if(curr)
        cout << curr->num << endl;

    cout << "Path Length: " << result[end_node].distance << endl;
}

int main()
{
    //Run's Dijkstra's algorithm on a sample adjacency list
    //Then prints results
    list<Vertex*>* adj_list;
    Vertex* result;
    int start_node, end_node;
    int num_nodes = 8;

    //Get nodes to find minimum path between
    start_node = get_input(num_nodes, 0);
    end_node = get_input(num_nodes, 1);

    //Create a sample adjacency list
    adj_list = build_adj_list();
    
    //Run Dijkstra's algorithm on the adjacency list
    result = run_dijkstras(adj_list, end_node);

    //Print results
    traverse_tree(start_node, end_node, result);

    delete adj_list;
    delete result;
}