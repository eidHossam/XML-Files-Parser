#pragma once
#include<bits/stdc++.h> 
#include "XML_Parser.h"

using namespace std;



class XML_to_json
{
private:
    string xml_Data;
    string json_output;
    string file_location;
    XML_Tree* file_tree_json;
    
    XML_Parser parser;
    vector<TreeNode*> tree_Nodes;
    


public:
   // XML_to_json();
    XML_to_json( XML_Parser parser);

    string json_string();
    void preOrderTraversalVectorFill(TreeNode * node) ;
    void printLevelOrder(TreeNode* root);

 
};
