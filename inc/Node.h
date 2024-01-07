#ifndef NODE_H_
#define NODE_H_
#include <iostream>
class huffman_node {
public:
    char id;
    int freq;
    std::string code;
    huffman_node* left;
    huffman_node* right;
    huffman_node();
};




#endif
