#include "../inc/XML_Decompressor.h"

void HuffmanDecompressor::constructTree(std::string& path, char character) {
    huffman_node* current = root;
    for (int i = 0; i < path.size(); i++) {
        if (path[i] == '0') {
            if (current->left == nullptr)
                current->left = new huffman_node();
            current = current->left;
        }
        else if (path[i] == '1') {
            if (current->right == nullptr)
                current->right = new huffman_node();
            current = current->right;
        }
    }
    current->id = character;
}
std::string HuffmanDecompressor::decompressFile(const std::string& compressedFile, const std::string& outputPath) {
    // Create a decompressor instance
    HuffmanDecompressor decompressor(compressedFile, outputPath);

    // Rebuild the Huffman tree
    decompressor.rebuildHuffmanTree();

    // Save the decompressed file
    decompressor.saveDecoding();

    // Read the decompressed content into a string
    std::ifstream decompressedFile(outputPath, std::ios::in | std::ios::binary);
    std::string decompressedString((std::istreambuf_iterator<char>(decompressedFile)),
    std::istreambuf_iterator<char>());
    decompressedFile.close();
    return decompressedString;

}
HuffmanDecompressor::HuffmanDecompressor(const std::string& input, const std::string& output)
    : root(nullptr), input_file_name(input), output_file_name(output) {}

void HuffmanDecompressor::rebuildHuffmanTree() {
    input_file.open(input_file_name, std::ios::in | std::ios::binary);
    unsigned char size;
    input_file.read(reinterpret_cast<char*>(&size), 1);
    root = new huffman_node;
    for (int i = 0; i < size; i++) {
        char character;
        unsigned char code_c[16];
        input_file.read(&character, 1);
        input_file.read(reinterpret_cast<char*>(code_c), 16);
        std::string code_string = "";
        for (int i = 0; i < 16; i++) {
            code_string += convertToBinary(code_c[i]);
        }
        int j = 0;
        while (code_string[j] == '0') {
            j++;
        }
        code_string = code_string.substr(j + 1);
        constructTree(code_string, character);
    }
    input_file.close();
}

std::string HuffmanDecompressor::convertToBinary(unsigned char num) {
    std::string result;
    for (int i = 7; i >= 0; --i) {
        result.push_back((num & (1 << i)) ? '1' : '0');
    }
    return result;
}

void HuffmanDecompressor::saveDecoding() {
    input_file.open(input_file_name, std::ios::in | std::ios::binary);
    output_file.open(output_file_name, std::ios::out);
    unsigned char size;
    input_file.read(reinterpret_cast<char*>(&size), 1);
    input_file.seekg(-1, std::ios::end);
    char count0;
    input_file.read(&count0, 1);
    input_file.seekg(1 + 17 * size, std::ios::beg);

    std::vector<unsigned char> encoded_text;
    unsigned char text_segment;
    input_file.read(reinterpret_cast<char*>(&text_segment), 1);
    while (!input_file.eof()) {
        encoded_text.push_back(text_segment);
        input_file.read(reinterpret_cast<char*>(&text_segment), 1);
    }
    huffman_node* current = root;
    std::string code_path;
    for (int i = 0; i < encoded_text.size() - 1; i++) {
        code_path = convertToBinary(encoded_text[i]);
        if (i == encoded_text.size() - 2)
            code_path = code_path.substr(0, 8 - count0);
        for (int j = 0; j < code_path.size(); j++) {
            if (code_path[j] == '0')
                current = current->left;
            else
                current = current->right;
            if (current->left == nullptr && current->right == nullptr) {
                output_file.put(current->id);
                current = root;
            }
        }
    }
    input_file.close();
    output_file.close();
}
