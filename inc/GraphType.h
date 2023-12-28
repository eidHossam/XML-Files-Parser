#pragma once
#include <bits/stdc++.h>
#include "XML_Parser.h"

using namespace std;

class GraphType
{
private:
    /* data */
    const int VERTICES_MAX; // Max number of vertices allowed in the graph.
    int vertices_count;     // Current number of vertices in the graph.
    string *vertices_arr;   // Array of vertices in the graph.
    int **adjacency_matrix; // Array of edges in the graph.

    vector<int> indegree;
    vector<int> outdegree;

public:
    /**
     * @brief Constructor for the GraphType
     *
     * @param Vertices_max: max allowed vertices in the graph.
     */
    GraphType(int Vertices_max);

    /**
     * @brief Adds a new vertex to the graph
     *
     * @param vertex: the vertex to be added.
     */
    void add_vertex(string vertex);

    /**
     * @brief Adds a new edge to the graph.
     *
     * @param src_vertex: The source vertex.
     * @param dest_vertex: The destination vertex.
     * @param weight: The weight of the edge.
     */
    void add_edge(string src_vertex, string dest_vertex, int weight);

    /**
     * @brief Gets the index of the given vertex.
     *
     * @param vertex
     * @return int return the index of the vertex if found, otherwise return -1.
     */
    int get_vertex_index(string vertex);

    /**
     * @brief Applys the depth first algorithm on the graph printing each vertex in its order.
     *
     * Note: This function takes the first vertex in the vertices array as the root.
     */
    void depth_first_traversal();

    /**
     * @brief Applys the breadth first algorithm on the graph printing each vertex in its order.
     *
     * Note: This function takes the first vertex in the vertices array as the root.
     */
    void breadth_first_traversal();

    void build_Graph(XML_Tree *file_tree);

    vector<int> getIndegree();

    vector<int> getOutdegree();

    vector<string> get_Vertices_Arr();



    /**
     * @brief Destructor of the GraphType
     */
    ~GraphType();
};
