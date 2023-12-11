#ifndef XML_COMPRESSOR_H_
#define XML_COMPRESSOR_H_

#include <unordered_map>
#include <queue>
#include <string>
#include "node.h"

class Compressor {
public:
    Compressor();
    std::string compress(const std::string& text);
    Node* getRoot() const;

private:
    Node* root;
    Node* getNode(char ch, int freq, Node* left, Node* right);
    struct comp;
    void Huffman_Encode(Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCode);
    void Calculate_Frequency_Map(std::unordered_map<char, int>& freq, const std::string& text);
    Node* Create_Huffman_Tree(std::priority_queue<Node*, std::vector<Node*>, comp>& PriorityQ, std::unordered_map<char, int>& freq);
};

#endif 
