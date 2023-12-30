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

    vector<string> posts = parser.findPosts("economy");

    for(auto post: posts)
    {
        cout << post << endl;
    }
    return 0;
}