#ifndef NODE_H_
#define NODE_H_
#include <iostream>
class huffman_node {
public:
    char id;
    int freq;
    std::string code;
    huffman_node* left=NULL;
    huffman_node* right=NULL;
};




#endif
