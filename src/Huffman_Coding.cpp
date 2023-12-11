/*
 * Huffman_Coding.cpp
 * ------------------------------
 * This file defines the methods of the HuffmanCoding class, which
 * encapsulates the compression and decompression functionalities
 * using Huffman Coding. It utilizes Compressor and Decompressor objects.
 * NOTE : Huffman encoding is a loseless compressing technique that is general for all texts not just XML but here we will use it to compress and decompress XML Files
 */
#include "Huffman_Coding.h"

HuffmanCoding::HuffmanCoding() : compressor(), decompressor() {}

std::string HuffmanCoding::compress(const std::string& text) {
    std::string Compressed_XML = compressor.compress(text);
	decompressor.Pass_Tree(compressor.getRoot());
	return Compressed_XML;
}

std::string HuffmanCoding::decompress(const std::string& text) {
    return decompressor.decompress(text);
}
