#include "GraphType.h"
#include <stdlib.h>

GraphType::GraphType(int Vertices_max) : VERTICES_MAX(Vertices_max)
{
    vertices_count = 0;
    
    vertices_arr = new string[VERTICES_MAX];        //Create an array of vertices with the size of the max vertices.
    adjacency_matrix = new int *[VERTICES_MAX];       //Create an array of pointers to integers.

    for (size_t i = 0; i < Vertices_max; i++)
    {
        adjacency_matrix[i] = new int[VERTICES_MAX];    //Create the the adjacency list for each vertex.
    }
    
}

void GraphType::breadth_first_traversal()
{
    if(0 == vertices_count)
    {
        return;
    }
    
    bool visited[vertices_count] = {false};
    queue<string> traversal_queue;

    traversal_queue.push(vertices_arr[0]);
    
    //Loop as long as the queue is not empty.
    while(!traversal_queue.empty())
    {
        string vertex = traversal_queue.front();
        traversal_queue.pop();

        int vertex_index = get_vertex_index(vertex);

        //Check if we aleady visited this node.
        if(!visited[vertex_index])
        {
            visited[vertex_index] = true;

            cout << "Vertex " << vertex << endl;
            
            for (size_t i = 0; i < vertices_count; i++)
            {
                //Add all the adjacent nodes to the traversal queue.
                if(!visited[i] && (adjacency_matrix[vertex_index][i] != 0))
                {
                    traversal_queue.push(vertices_arr[i]);
                }
            }
        }
    }
}

GraphType::~GraphType() {
  delete[] vertices_arr; // Deallocate memory of the vertices.

  for (size_t i = 0; i < VERTICES_MAX; i++) {
    delete[] adjacency_matrix[i];
  }

  delete[] adjacency_matrix;
}

void GraphType::add_edge(string src_vertex,
                                     string dest_vertex, int weight)
{
    int row = get_vertex_index(src_vertex);
    int col = get_vertex_index(dest_vertex);

    adjacency_matrix[row][col] = weight;
}

int GraphType::get_vertex_index(string vertex) {
    int index = -1;
    for (size_t i = 0; i < VERTICES_MAX; i++)
    {
        if(vertices_arr[i] == vertex)
        {
            index = i;
            break;
        }
    }
  return index;
}

void GraphType::depth_first_traversal()
{
    if(0 == vertices_count)
    {
        return;
    }
    
    bool visited[vertices_count] = {false};
    stack<string> traversal_stack;

    traversal_stack.push(vertices_arr[0]);

    //Loop as long as the stack is not empty.
    while(!traversal_stack.empty())
    {
        string vertex = traversal_stack.top();
        traversal_stack.pop();

        int vertex_index = get_vertex_index(vertex);
        
        //Check if we aleady visited this node.
        if(!visited[vertex_index])
        {
            visited[vertex_index] = true;

            cout << "Vertex " << vertex << endl;
            
            for (size_t i = 0; i < vertices_count; i++)
            {
                //Add all the adjacent nodes to the traversal stack.
                if(!visited[i] && (adjacency_matrix[vertex_index][i] != 0))
                {
                    traversal_stack.push(vertices_arr[i]);
                }
            }            
        }
    }
    
}

void GraphType::add_vertex(string vertex) 
{
    vertices_arr[vertices_count] = vertex;

    //Initialize all the edges of this vertex to zero.
    for (size_t i = 0; i < VERTICES_MAX; i++)
    {
        adjacency_matrix[vertices_count][i] = 0;
        adjacency_matrix[i][vertices_count] = 0;
    }
    
    vertices_count++;
}
