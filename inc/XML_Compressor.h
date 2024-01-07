#ifndef XML_COMPRESSOR_H_
#define XML_COMPRESSOR_H_

#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include "Node.h"

class HuffmanCompressor {
private:
    class compare {
    public:
        bool operator()(const huffman_node* c1, const huffman_node* c2) const {
            return c1->freq > c2->freq;
        }
    };

    huffman_node* node_array[128];
    std::ifstream in_file;
    std::ofstream out_file;
    huffman_node* root;
    std::string inFileName;
    std::string outFileName;
    std::priority_queue<huffman_node*, std::vector<huffman_node*>, compare> pq;

    void createNodeArray();
    void traverse(huffman_node* node, std::string code);
    int binaryToDecimal(const std::string& in);  
    void buildTree(std::string& path, char aCode);
    void createPriorityQueue();
    void createHuffmanTree();
    void calculateHuffmanCodes();
    void saveCompressedFile();

public:
    HuffmanCompressor(const std::string& input, const std::string& output);
    std::string compressFile(const std::string& inputFile, const std::string& outputPath);

};

#endif