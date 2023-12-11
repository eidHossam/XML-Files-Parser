#pragma once
#include <bits/stdc++.h> 
#include "tree.h"
#include <sstream>

using namespace std;

class XML_Parser
{
private:
    string file_location;
    string original_xml_data;
    string fixed_xml_data;
    string formated_xml_data;

    XML_Tree* file_tree;

    string get_xml_data( int formatting);
    
    void trim(string& str);
    
    string extract_data_field(string line);

    void printXML(TreeNode* node, int depth);
public:
    XML_Parser();
    XML_Parser(string file_location);
    
    string get_raw_xml_data();

    string get_formatted_xml_data();

    bool has_errors();

    string fix_xml_data();

    string xml_format();

    XML_Tree* build_xml_tree();

/** @defgroup Getters
  * @{
  */
    string get_original_xml_data();

    string get_fixed_xml_data();
/**
  * @}
  */
};

