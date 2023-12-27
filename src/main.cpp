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
#include "GraphType.h"

using namespace std;

int main()
{
    
    string _xml_data;
    XML_Parser parser("src/sample.xml");
    XML_to_json test(parser);
    XML_Tree* file_tree=parser.build_xml_tree();
    _xml_data = parser.xml_format();
    vector<TreeNode*> users=file_tree->root->no_Of_Users_Vector();
    GraphType graph(users.size());
    graph.build_Graph(file_tree);

    // vector<vector<string>> followersidsss=file_tree->root->followersID();
    // vector<TreeNode*> userids=file_tree->root->id_Of_Users();
    // GraphType graph(users.size());
    // for(auto var : userids)
    // {
    //     graph.add_vertex(var->_tag_data);
    // }
    // for (int i = 0; i < userids.size(); i++)
    // {
    //     for (int j = 0; j <followersidsss[i].size(); j++)
    //     {   
            
    //         graph.add_edge(userids[i]->_tag_data,followersidsss[i][j],1);
    //     }
        
    // }
    graph.depth_first_traversal();
    // cout<<followersidsss[0].size();
    // cout<<followersidsss[1].size();
    // cout<<followersidsss[2].size();

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