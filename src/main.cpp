#include <iostream>
#include <string.h>
#include <fstream>
#include <bits/stdc++.h> 
#include <stack>
#include <queue>
#include <list>
#include <forward_list>
#include "tree.h"
#include "XML_Parser.h"


using namespace std;

int main()
{
    string _xml_data;
    XML_Parser parser("src/sample.xml");
    _xml_data = parser.get_raw_xml_data();

    cout << _xml_data << endl;
    
    vector<string> vec = parser.highlight_errors();

    for(string s : vec)
    {
        cout << s << endl;
    }
    return 0;
}