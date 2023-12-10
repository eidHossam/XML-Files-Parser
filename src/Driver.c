#include "../inc/XML_Compressor.h"
#include "../inc/XML_Decompressor.h"
#include <iostream>
using namespace std;
int main() {
    // Example XML data
    string xml_data = "<users><user><id>1</id><name>John Doe</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>technology</topic><topic>programming</topic></topics></post><post><body>Another post about interesting things. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>science</topic><topic>innovation</topic></topics></post></posts><followers><follower><id>2</id></follower><follower><id>3</id></follower></followers></user><user><id>2</id><name>Jane Smith</name><posts><post><body>Exploring the wonders of the natural world. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>environment</topic><topic>biology</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user><user><id>3</id><name>Alice Johnson</name><posts><post><body>Sharing thoughts on the latest literary works. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>books</topic><topic>literature</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user></users>";

    // Compression
    string compressedXML = Huffman_Compress(xml_data);
    cout << "CompressedXML is:\n----------------------\n" << compressedXML << "\n\n";

    // Decompression
    string decompressedXML = Huffman_Decompress(compressedXML);
    cout << "DecompressedXML is:\n----------------------\n" << decompressedXML << "\n\n";

    // Original and compressed sizes
    cout << "\nOriginal size: " << xml_data.size() << " bytes" << endl;
    cout << "Compressed size: " << compressedXML.size() / 8 << " bytes" << endl;

    return 0;
}
