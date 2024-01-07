#ifndef XML_DECOMPRESSOR_H_
#define XML_DECOMPRESSOR_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Node.h"

class HuffmanDecompressor {
private:
    std::ifstream input_file;
    std::ofstream output_file;
    huffman_node* root = nullptr;
    char identifier;
    std::string input_file_name;
    std::string output_file_name;

    std::string convertToBinary(unsigned char num);
    void constructTree(std::string& path, char character);

public:
    HuffmanDecompressor(const std::string& input, const std::string& output);
    void rebuildHuffmanTree();
    void saveDecoding();
    std::string decompressFile(const std::string& compressedFile, const std::string& outputPath);
};

#endif
