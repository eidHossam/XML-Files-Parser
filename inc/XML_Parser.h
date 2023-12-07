#pragma once
#include <bits/stdc++.h> 
#include "tree.h"

using namespace std;

class XML_Parser
{
private:
    string original_xml_data;
    string fixed_xml_data;
public:
    XML_Parser();

    string get_xml_data(string file_location);
    
    bool has_errors(string data);

    string extract_data_field(string line);
    
    string fix_xml_data(string file_location);

    XML_Tree check_consistency(string data);

};

