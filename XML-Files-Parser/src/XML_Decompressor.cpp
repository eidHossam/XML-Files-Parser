/*
 * XML_Decompressor.cpp
 * ------------------------------
 * This file defines the methods of the Decompressor class, responsible
 * for decompressing XML data using the Huffman tree provided by the Compressor.
 */
#include "../inc/XML_Decompressor.h"

Decompressor::Decompressor() : root(nullptr) {}

char Decompressor::Huffman_Decode(Node* root, int& index, const std::string& str) {
    if (index >= (int)str.size() || root == nullptr) {
        return '\0';
    }
    if (!root->left && !root->right) {
        return root->ch;
    }
    index++;
    if (str[index] == '0') {
        return Huffman_Decode(root->left, index, str);
    }
    else {
        return Huffman_Decode(root->right, index, str);
    }
}
void Decompressor::Pass_Tree(Node * root)
{
	this->root = root;
}

std::string Decompressor::decompress(const std::string& text) {
    std::string decompressedText = "";
    int index = -1;
    while (index < (int)text.size() - 2) {
        decompressedText += Huffman_Decode(root, index, text);
    }
    return decompressedText;
}
