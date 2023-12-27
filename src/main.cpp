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

    _xml_data = parser.get_formatted_xml_data();
    _xml_data = parser.fix_xml_data();
    _xml_data = parser.highlight_errors();

    cout << _xml_data;
    return 0;
}