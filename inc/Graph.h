#pragma once
#include<bits/stdc++.h> 
#include"XML_to_json.h"
using namespace std;


// stores adjacency list items
struct adjNode {
    int val, cost;
    adjNode* next;
};
// structure to store edges
struct graphEdge {
    int start_ver, end_ver, weight;
};
class DiaGraph{
    // insert new nodes into adjacency list from given graph
    adjNode* getAdjListNode(int value, int weight, adjNode* head);
    int N;  // number of nodes in the graph
public:
    adjNode **head;                //adjacency list as array of pointers
    // Constructor
    DiaGraph(graphEdge edges[], int n, int N) ;
      // Destructor
    ~DiaGraph() ;
    void display_AdjList(adjNode* ptr, int i);
};
// print all adjacent vertices of given vertex
