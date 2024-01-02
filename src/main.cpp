#include <iostream>
#include "../inc/XML_Compressor.h"
#include "../inc/XML_Decompressor.h"

int main() {
    // Compression Example
    std::string inputFilePath = "test.txt";
    std::string compressedFilePath = "compressedFile.bin";

    // Create an object of HuffmanCompressor
    HuffmanCompressor compressor(inputFilePath, compressedFilePath);

    // Perform compression and save to file
    compressor.compressFile(inputFilePath, compressedFilePath);

    // Decompression Example
    std::string decompressedFilePath = "decompressedFile.xml";

    // Create an object of HuffmanDecompressor
    HuffmanDecompressor decompressor(compressedFilePath, decompressedFilePath);

    // Perform decompression and save to file
    decompressor.decompressFile(compressedFilePath, decompressedFilePath);

    return 0;
}
