#include "../inc/XML_Decompressor.h"
#include "../inc/Node.h"


char Huffman_Decode(Node* root, int& index, std::string str) {
    if (index >= (int)str.size() || root == nullptr) {
        return '\0';  // Return a default character when encountering the end of the string or a non-leaf node
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

std::string Huffman_Decompress(std::string text) {
    std::string DecompressedXML = "";
    int index = -1;
    while (index < (int)text.size() - 2) {
        DecompressedXML += Huffman_Decode(root, index, text);
    }
    return DecompressedXML;
}
