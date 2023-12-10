#ifndef NODE_H_
#define NODE_H_

struct Node {
    char ch;
    int freq;
    Node* left, * right;
};

extern Node* root;

Node* getNode(char ch, int freq, Node* left, Node* right);

#endif
