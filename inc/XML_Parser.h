#pragma once
#include <bits/stdc++.h> 
#include "tree.h"
#include <sstream>

using namespace std;

class XML_Parser
{
private:
    string original_xml_data;
    string fixed_xml_data;
public:
    XML_Parser();

    string get_xml_data(string file_location);
    
    void trim(string& str);

    bool has_errors(string data);

    string extract_data_field(string line);
    
    string fix_xml_data(string file_location);

    string xml_format(string xml_data);

    XML_Tree build_xml_tree(string data);

};

