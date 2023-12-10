#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_

#include <unordered_map>
#include <queue>
#include <string>
#include "Node.h"

struct comp {
    bool operator()(Node* l, Node* r);
};

void Huffman_Encode(Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCode);
void Calculate_Frequency_Map(std::unordered_map<char, int>& freq, std::string text);
Node* Create_Huffman_Tree(std::priority_queue<Node*, std::vector<Node*>, comp>& PriorityQ, std::unordered_map<char, int>& freq);
std::string Huffman_Compress(std::string text);

#endif
