#include <iostream>
#include <list>
#include <iterator>
#include <stack>
#include <queue>

using namespace std;

int matrix[10][10]  = {
                    {0,1,0,0,0,0,0,1,0,0},
                    {1,0,1,1,0,0,1,0,0,0},
                    {0,1,0,0,0,0,0,0,0,0},
                    {0,1,0,0,1,1,0,0,0,0},
                    {0,0,0,1,0,0,0,0,0,0},
                    {0,0,0,1,0,0,0,0,0,0},
                    {0,1,0,0,0,0,0,0,0,0},
                    {1,0,0,0,0,0,0,0,1,1},
                    {0,0,0,0,0,0,0,1,0,0},
                    {0,0,0,0,0,0,0,1,0,0},
                    };

/* ---------------------------- Debug ---------------------------- */

void print_list(list<int>* adj_list)
{
    //Print an adjacency list
    int num_nodes = sizeof(*matrix)/sizeof(**matrix);
    list<int>::iterator adj_node;

    for(int node_list = 0; node_list < num_nodes; node_list++)
    {
        for(adj_node = adj_list[node_list].begin(); 
            adj_node != adj_list[node_list].end(); adj_node++)
            cout << *adj_node << " ";

        cout << endl;
    }
}

/* --------------------------------------------------------------- */

list<int>* matrix_to_list(int num_nodes) {

    //Dynamically create an array containing a list for each node.
    list<int>* adj_list = new list<int>[num_nodes]; 

    //Populate the lists in the array from the matrix
    for(int node_list = 0; node_list < num_nodes; node_list++)
        for(int node = 0; node < num_nodes; node++ )
            if(matrix[node_list][node] == 1)
                adj_list[node_list].push_back(node);

    return adj_list;
}

void run_bfs(list<int>* adj_list, int num_nodes)
{
    queue<int> nodes_to_visit;
    list<int>::iterator adj_node;
    int visited_node_count = 0;
    bool* visited_nodes = new bool[num_nodes]; 

    cout << "BFS Result: "; 

    //Add first node to queue
    nodes_to_visit.push(0);

    //Until all nodes are visited:
    while(visited_node_count < num_nodes)
    {
        //Get the next node from the queue
        int node_to_visit = nodes_to_visit.front();
        
        //Add all unvisited adjacent nodes to the queue
        for(adj_node = adj_list[node_to_visit].begin(); 
            adj_node != adj_list[node_to_visit].end(); adj_node++)
            if(visited_nodes[*adj_node] == 0)
                nodes_to_visit.push(*adj_node);
    
        //Remove visited node and mark as visited
        nodes_to_visit.pop();
        visited_nodes[node_to_visit] = 1;
        visited_node_count++;

        //Print visited node
        cout << node_to_visit << " ";
    }

    cout << endl;
}

void run_dfs(list<int>* adj_list, int num_nodes)
{
    cout << "Running DFS" << endl;
}

int main() {

    //Create an adjacency list from an adjacency matrix
    list<int>* adj_list;
    int num_nodes = sizeof(*matrix)/sizeof(**matrix);
    
    adj_list =  matrix_to_list(num_nodes);

    //Run a Breadth-First Search of the graph
    run_bfs(adj_list, num_nodes);

    //Run a Depth-First Search of the graph
    run_dfs(adj_list, num_nodes);

    //print_list(adj_list);

}