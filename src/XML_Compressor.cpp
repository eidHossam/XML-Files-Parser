#include "../inc/XML_Compressor.h"
#include <iostream>
#include <fstream>
#include "../inc/Node.h"
void HuffmanCompressor::createNodeArray() {
    for (int i = 0; i < 128; i++) {
        node_array[i] = new huffman_node;
        node_array[i]->id = i;
        node_array[i]->freq = 0;
        node_array[i]->left = nullptr;  // Initialize left and right pointers
        node_array[i]->right = nullptr;
    }
}

std::string HuffmanCompressor::compressFile(const std::string& inputFile, const std::string& outputPath) {
    // Create a compressor instance
    HuffmanCompressor compressor(inputFile, outputPath);

    // Perform compression steps
    compressor.createPriorityQueue();
    compressor.createHuffmanTree();
    compressor.calculateHuffmanCodes();
    compressor.saveCompressedFile();

    // Optionally, read the compressed file content into a string
    std::string compressedString;
    std::ifstream compressedFile(outputPath, std::ios::binary);
    compressedString = std::string((std::istreambuf_iterator<char>(compressedFile)), std::istreambuf_iterator<char>());

    return compressedString;
}
void HuffmanCompressor::traverse(huffman_node* node, std::string code) {
    if (node->left == nullptr && node->right == nullptr) {
        node->code = code;
    }
    else {
        traverse(node->left, code + '0');
        traverse(node->right, code + '1');
    }
}

int HuffmanCompressor::binaryToDecimal(const std::string& in) {
    int result = 0;
    for (int i = 0; i < in.size(); i++)
        result = result * 2 + in[i] - '0';
    return result;
}

void HuffmanCompressor::buildTree(std::string& path, char aCode) {
    huffman_node* current = root;
    for (int i = 0; i < path.size(); i++) {
        if (path[i] == '0') {
            if (current->left == nullptr)
                current->left = new huffman_node;
            current = current->left;
        }
        else if (path[i] == '1') {
            if (current->right == nullptr)
                current->right = new huffman_node;
            current = current->right;
        }
    }
    current->id = aCode;
}

HuffmanCompressor::HuffmanCompressor(const std::string& in, const std::string& out) : root(nullptr), inFileName(in), outFileName(out) {
    createNodeArray();
}

void HuffmanCompressor::createPriorityQueue() {
    in_file.open(inFileName, std::ios::in);
    char id;
    in_file.get(id);
    while (!in_file.eof()) {
        node_array[id]->freq++;
        in_file.get(id);
    }
    in_file.close();

    for (int i = 0; i < 128; i++) {
        if (node_array[i]->freq) {
            pq.push(node_array[i]);
        }
    }
}

void HuffmanCompressor::createHuffmanTree() {
    std::priority_queue<huffman_node*, std::vector<huffman_node*>, compare> temp(pq);

    while (temp.size() > 1) {
        root = new huffman_node;
        root->freq = 0;
        root->left = temp.top();
        root->freq += root->left->freq;
        temp.pop();
        root->right = temp.top();
        root->freq += root->right->freq;
        temp.pop();
        temp.push(root);
    }
}

void HuffmanCompressor::calculateHuffmanCodes() {
    traverse(root, "");
}
void HuffmanCompressor::saveCompressedFile() {
    in_file.open(inFileName, std::ios::in);
    out_file.open(outFileName, std::ios::out | std::ios::binary);

    std::string in = "", s = "";

    in += static_cast<char>(pq.size());
    std::priority_queue<huffman_node*, std::vector<huffman_node*>, compare> temp(pq);
    while (!temp.empty()) {
        huffman_node* current = temp.top();
        in += current->id;
        s.assign(127 - current->code.size(), '0');
        s += '1';
        s.append(current->code);
        in += static_cast<char>(binaryToDecimal(s.substr(0, 8)));
        for (int i = 0; i < 15; i++) {
            s = s.substr(8);
            in += static_cast<char>(binaryToDecimal(s.substr(0, 8)));
        }
        temp.pop();
    }
    s.clear();

    char id;
    in_file.get(id);
    while (!in_file.eof()) {
        s += node_array[id]->code;
        while (s.size() > 8) {
            in += static_cast<char>(binaryToDecimal(s.substr(0, 8)));
            s = s.substr(8);
        }
        in_file.get(id);
    }
    int count = 8 - s.size();
    if (s.size() < 8) {
        s.append(count, '0');
    }
    in += static_cast<char>(binaryToDecimal(s));
    in += static_cast<char>(count);

    out_file.write(in.c_str(), in.size());
    in_file.close();
    out_file.close();
}