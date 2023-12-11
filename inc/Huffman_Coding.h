#ifndef HUFFMAN_CODING_H_
#define HUFFMAN_CODING_H_

#include "XML_Compressor.h"
#include "XML_Decompressor.h"
//NOTE : Huffman encoding is a loseless compressing technique that is general for all texts not just XML but here we will use it to compress and decompress XML Files
class HuffmanCoding {
public:
    HuffmanCoding();
    std::string compress(const std::string& text);
    std::string decompress(const std::string& text);

private:
    Compressor compressor;
    Decompressor decompressor;
};

#endif 
