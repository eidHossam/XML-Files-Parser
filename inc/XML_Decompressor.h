#ifndef XML_DECOMPRESSOR_H_
#define XML_DECOMPRESSOR_H_

#include <string>
#include "node.h"

char Huffman_Decode(Node* root, int& index, std::string str);
std::string Huffman_Decompress(std::string text);

#endif
