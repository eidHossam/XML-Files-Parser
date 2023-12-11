/*
 * main.cpp
 * ------------------------------
 * This file contains the main function demonstrating the usage
 * of Huffman Coding to compress and decompress XML data.
 */
#include <iostream>
#include <fstream>
#include "huffman_coding.h"

std::string get_xml_data(const std::string& file_location) {
    std::ifstream xml_file(file_location);

    std::string xml_data, tmp;
    if (xml_file.is_open()) {
        while (getline(xml_file, tmp)) {
            xml_data = xml_data + tmp + "\n";
        }
    }
    return xml_data;
}

int main() {
    std::string xml_data = get_xml_data("sample.xml");

    HuffmanCoding huffmanCoding;
    std::string compressedXML = huffmanCoding.compress(xml_data);
    std::cout << "Compressed XML:\n" << compressedXML << "\n";

    std::string decompressedXML = huffmanCoding.decompress(compressedXML);
    std::cout << "\nDecompressed XML:\n" << decompressedXML << "\n";

    std::cout << "\nOriginal size: " << xml_data.size() << " bytes" << std::endl;
    std::cout << "Compressed size: " << compressedXML.size() / 8 << " bytes" << std::endl;

    return 0;
}
