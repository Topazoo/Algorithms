#include <iostream>
#include <list>
#include <iterator>
#include <stack>
#include <queue>
#include<limits>

using namespace std;

const int num_mats = 2;

const int matrix[10][10]  = {
                    {0,1,0,0,0,0,0,1,0,0},//               0   
                    {1,0,1,1,0,0,1,0,0,0},//              / \.
                    {0,1,0,0,0,0,0,0,0,0},//             /   7
                    {0,1,0,0,1,1,0,0,0,0},//            1   / \.
                    {0,0,0,1,0,0,0,0,0,0},//           /|\ 8   9
                    {0,0,0,1,0,0,0,0,0,0},//          2 3 6
                    {0,1,0,0,0,0,0,0,0,0},//           /\.
                    {1,0,0,0,0,0,0,0,1,1},//          4  5
                    {0,0,0,0,0,0,0,1,0,0},
                    {0,0,0,0,0,0,0,1,0,0},
                    };

const int matrix2[10][10]  = {    //Disjoint
                    {0,1,1,0,0,0,0,0,0,0},//   3 --- 4        5
                    {1,0,1,1,0,0,0,0,0,0},//   |     |       / \.
                    {1,1,0,0,1,0,0,0,0,0},//   |     |      /  6
                    {0,1,0,0,1,0,0,0,0,0},//   1 --- 2     /  / 
                    {0,0,1,1,0,0,0,0,0,0},//    \   /     /  7 
                    {0,0,0,0,0,0,1,0,0,1},//     \ /      | /
                    {0,0,0,0,0,1,0,1,0,0},//      0       9 --- 8
                    {0,0,0,0,0,0,1,0,0,1},
                    {0,0,0,0,0,0,0,0,0,1},
                    {0,0,0,0,0,1,0,1,1,0},
                    };

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

list<int>* matrix2_to_list(int num_nodes) {

    //Dynamically create an array containing a list for each node.
    list<int>* adj_list = new list<int>[num_nodes]; 

    //Populate the lists in the array from the matrix
    for(int node_list = 0; node_list < num_nodes; node_list++)
        for(int node = 0; node < num_nodes; node++ )
            if(matrix2[node_list][node] == 1)
                adj_list[node_list].push_back(node);

    return adj_list;
}

void run_bfs(list<int>* adj_list, int num_nodes, int start_node)
{
    queue<int> nodes_to_visit;
    list<int>::iterator adj_node;
    bool* visited_nodes = new bool[num_nodes](); 

    cout << "BFS Result: "; 

    //Add first node to queue
    nodes_to_visit.push(start_node);
    visited_nodes[start_node] = 1;

    //Until all nodes are visited:
    while(! nodes_to_visit.empty())
    {
        //Get the next node from the queue
        int node_to_visit = nodes_to_visit.front();
        
        //Remove visited node and mark as visited
        nodes_to_visit.pop();
        
        //Add all unvisited adjacent nodes to the queue
        for(adj_node = adj_list[node_to_visit].begin(); 
            adj_node != adj_list[node_to_visit].end(); adj_node++)
            if(visited_nodes[*adj_node] == 0)
            {
                nodes_to_visit.push(*adj_node);
                visited_nodes[*adj_node] = 1;
            }
        //Print visited node
        cout << node_to_visit << " ";
    }

    cout << endl;
}

void run_dfs(list<int>* adj_list, int num_nodes, 
                bool* visited_nodes, int start_node)
{
    list<int>::iterator adj_node;

    //If first recursive step, create list of visited nodes
    if(! visited_nodes)
    {
        visited_nodes = new bool[num_nodes]();
        cout << "DFS Result: "; 
    }

    //Mark node as visited
    cout << start_node << " ";

    visited_nodes[start_node] = 1;

    //Recurse on all unvisited children
    for(adj_node = adj_list[start_node].begin(); 
        adj_node != adj_list[start_node].end(); adj_node++)
        if(visited_nodes[*adj_node] == 0)
            run_dfs(adj_list, num_nodes, visited_nodes, *adj_node);
        
}

int get_input_matrix()
{
    //Matrix to perform search on

    int mat = 0;

    cout << "Choose a Matrix:" << endl;

    for(int i = 1; i <= num_mats; i++)
        cout << "Matrix " << i << endl;

    cout << ">>> ";

    while(! (cin >> mat) || mat < 1 || mat > num_mats)
    {
        cout << "Choose a Matrix:" << endl;

        for(int i = 1; i <= num_mats; i++)
            cout << "Matrix " << i << endl;

        cout << ">>> ";

        //Clear old input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return mat;
}

int get_input_start(int num_nodes)
{
    int start = -1;

    cout << "Choosing a starting node between 0 and " << num_nodes - 1 << endl;
    cout << ">>> ";

    while(! (cin >> start) || start < 0 || start >= num_nodes)
    {
        cout << "Choosing a starting node between 0 and " << num_nodes - 1 << endl;
        cout << ">>> ";

        //Clear old input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return start;
}

int main() {

    list<int>* adj_list;
    int num_nodes, mat, start;

    //User chooses matrix
    mat = get_input_matrix();

    //Create an adjacency list from an adjacency matrix
    if(mat == 1)
    {
        num_nodes = sizeof(*matrix)/sizeof(**matrix);
        adj_list =  matrix_to_list(num_nodes);
    }

    else if(mat == 2)
    {
        num_nodes = sizeof(*matrix2)/sizeof(**matrix2);
        adj_list =  matrix2_to_list(num_nodes);
    }    

    start = get_input_start(num_nodes);

    //Run a Breadth-First Search of the graph
    run_bfs(adj_list, num_nodes, start);

    //Run a Depth-First Search of the graph
    run_dfs(adj_list, num_nodes, NULL, start);
    
    cout << endl;

}