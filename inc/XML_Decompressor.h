#ifndef XML_DECOMPRESSOR_H_
#define XML_DECOMPRESSOR_H_

#include "Node.h"
#include <string>

using namespace std;

string Huffman_Decompress(string text);
char Huffman_Decode(Node* root, int& index, string str);

#endif
