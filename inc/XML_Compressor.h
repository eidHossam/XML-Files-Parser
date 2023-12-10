#ifndef XML_COMPRESSOR_H_
#define XML_COMPRESSOR_H_

#include "Node.h"
#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

struct comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

Node* getNode(char ch, int freq, Node* left, Node* right);
void Huffman_Encode(Node* root, string str, unordered_map<char, string>& huffmanCode);
void Calculate_Frequency_Map(unordered_map<char, int>& freq, string text);
Node* Create_Huffman_Tree(priority_queue<Node*, vector<Node*>, comp>& PriorityQ, unordered_map<char, int>& freq);
string Huffman_Compress(string text);

#endif
