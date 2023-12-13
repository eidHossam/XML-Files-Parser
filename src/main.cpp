// #include <iostream>
// #include <string.h>
// #include <fstream>
// #include <bits/stdc++.h> 
// #include <stack>
// #include <queue>
// #include <list>
// #include <forward_list>
// #include "tree.h"
// #include "XML_Parser.h"
#include "XML_to_json.h"


using namespace std;

int main()
{
    
    string _xml_data;
    XML_Parser parser("src/sample.xml");
    XML_to_json test(parser);
    XML_Tree* file_tree=parser.build_xml_tree();
    _xml_data = parser.xml_format();
    //cout<<_xml_data;
    //cout << test.json_string();
    cout<<file_tree->root->similar_Brothers();
    cout<<file_tree->root->_tag_name;

     // Create and open a text file
    ofstream json_file("test.json");

     // Write to the file
    while(1){
        json_file<< test.json_string();
        break;
    }
     // Close the file
    json_file.close();
    return 0;
}