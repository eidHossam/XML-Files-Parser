#include "../inc/XML_Compressor.h"
#include "../inc/Node.h"

Node* root = nullptr;

Node* getNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

bool comp::operator()(Node* l, Node* r) {
    return l->freq > r->freq;
}

void Huffman_Encode(Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCode) {
    if (root == nullptr)
        return;
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }
    Huffman_Encode(root->left, str + "0", huffmanCode);
    Huffman_Encode(root->right, str + "1", huffmanCode);
}

void Calculate_Frequency_Map(std::unordered_map<char, int>& freq, std::string text) {
    for (char ch : text) {
        freq[ch]++;
    }
}

Node* Create_Huffman_Tree(std::priority_queue<Node*, std::vector<Node*>, comp>& PriorityQ, std::unordered_map<char, int>& freq) {
    for (auto pair : freq) {
        PriorityQ.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (PriorityQ.size() != 1) {
        Node* left = PriorityQ.top(); PriorityQ.pop();
        Node* right = PriorityQ.top(); PriorityQ.pop();
        int sum = left->freq + right->freq;
        PriorityQ.push(getNode('\0', sum, left, right));
    }

    return PriorityQ.top(); // Return the lost node remaining in PQ, which is the root of the Huffman tree
}

std::string Huffman_Compress(std::string text) {
    std::unordered_map<char, int> freq;
    Calculate_Frequency_Map(freq, text);
    std::priority_queue<Node*, std::vector<Node*>, comp> PriorityQ;
    root = Create_Huffman_Tree(PriorityQ, freq);
    std::unordered_map<char, std::string> huffmanCode;
    Huffman_Encode(root, "", huffmanCode);

    // Obtaining the compressedXML from huffman code and the original XML
    std::string CompressedXML = "";
    for (char ch : text) {
        CompressedXML += huffmanCode[ch];
    }
    return CompressedXML;
}
