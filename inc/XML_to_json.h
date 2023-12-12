#pragma once
#include "XML_Parser.h"

//using namespace std;



class XML_to_json
{
private:
    string xml_Data;
    string json_output_string;
    XML_Tree* file_tree_json;
    XML_Parser parser;
    vector<TreeNode*> tree_Nodes;
    string tabs(int level);


public:
    XML_to_json( XML_Parser parser);
    string json_string();
    void json_string_builder(TreeNode * node);
    void preOrderTraversalVectorTagsFill(TreeNode * node) ;
   
 
};
