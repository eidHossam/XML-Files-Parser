/*
 * XML_Compressor.cpp
 * ------------------------------
 * This file defines the methods of the Compressor class, which handles
 * XML compression using Huffman Coding. It creates a Huffman tree, encodes
 * XML data, and provides the root of the tree for decompression.
 */
#include "../inc/XML_Compressor.h"

Compressor::Compressor() : root(nullptr) {}

Node* Compressor::getNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

struct Compressor::comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void Compressor::Huffman_Encode(Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCode) {
    if (root == nullptr)
        return;
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }
    Huffman_Encode(root->left, str + "0", huffmanCode);
    Huffman_Encode(root->right, str + "1", huffmanCode);
}

void Compressor::Calculate_Frequency_Map(std::unordered_map<char, int>& freq, const std::string& text) {
    for (char ch : text) {
        freq[ch]++;
    }
}

Node* Compressor::Create_Huffman_Tree(std::priority_queue<Node*, std::vector<Node*>, comp>& PriorityQ, std::unordered_map<char, int>& freq) {
    for (auto pair : freq) {
        PriorityQ.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (PriorityQ.size() != 1) {
        Node* left = PriorityQ.top(); PriorityQ.pop();
        Node* right = PriorityQ.top(); PriorityQ.pop();
        int sum = left->freq + right->freq;
        PriorityQ.push(getNode('\0', sum, left, right));
    }

    return PriorityQ.top();
}

std::string Compressor::compress(const std::string& text) { //Pass by reference to avoid overhead of copying data and for memory management purpose
    std::unordered_map<char, int> freq;
    Calculate_Frequency_Map(freq, text);
    std::priority_queue<Node*, std::vector<Node*>, comp> PriorityQ;
    root = Create_Huffman_Tree(PriorityQ, freq);
    std::unordered_map<char, std::string> huffmanCode;
    Huffman_Encode(root, "", huffmanCode);

    std::string compressedText = "";
    for (char ch : text) {
        compressedText += huffmanCode[ch];
    }
    return compressedText;
}

Node* Compressor::getRoot() const {
    return root;
}
