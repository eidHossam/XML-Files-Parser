#ifndef XML_DECOMPRESSOR_H_
#define XML_DECOMPRESSOR_H_

#include <string>
#include "Node.h"

class Decompressor {
public:
    Decompressor();
    std::string decompress(const std::string& text);
	void Pass_Tree(Node * root);
private:
    Node* root;
    char Huffman_Decode(Node* root, int& index, const std::string& str);
};


#endif 