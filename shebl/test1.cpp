#include<iostream>
#include<string.h>
#include <fstream>
#include<bits/stdc++.h> 
#include <stack>
#include <queue>
#include <list>
#include <forward_list>
#include "tree.cpp"

using namespace std;
// int main()
// {
    
//     ifstream _xml_file("C:\\Users\\youssef\\Desktop\\programing\\DS_c++\\Project\\sample.xml");

//     string _xml_data,tmp;
//     if( _xml_file.is_open())
//     {
//         while (getline(_xml_file,tmp))
//         {
           
//             _xml_data=_xml_data+tmp; //_xml_data.append(tmp);
//         }
//     }
//     //cout<<_xml_data;
//     //_xml_data.erase(std::remove_if(_xml_data.begin(), _xml_data.end(), "\t"), _xml_data.end());
    
//     // regex _tag_regex("<([^<>]+)>");
//     // sregex_iterator _tag_iterator(_xml_data.begin(),_xml_data.end(),_tag_regex);
//     // sregex_iterator _endtag_iterator; 
   
//     // //"\\(([^)]+)\\)"
//     // XML_Tree tree;
//     // bool flag=false;
//     // while (_tag_iterator !=_endtag_iterator ) {
//     //     std::smatch match = *_tag_iterator;
//     //     //Here
       
//     //     cout<<match.str()<<endl;
//     //     ++_tag_iterator;
//     // }


    
//     regex _info_regex( "<(topic|id|name|body)>(.*?)</(topic|id|name|body)>" );

//     sregex_iterator _info_iterator(_xml_data.begin(),_xml_data.end(),_info_regex);
//     sregex_iterator _endinfo_iterator; 
//     while (_info_iterator !=_endinfo_iterator ) {
//         std::smatch match = *_info_iterator;
//         cout<<match.str()<<endl;
//         ++_info_iterator;
//     }

//     return 0;
// }
int main()
{
    ifstream _xml_file("C:\\Users\\youssef\\Desktop\\programing\\DS_c++\\Project\\sample.xml");

    string _xml_data,tmp;
    if( _xml_file.is_open())
    {
        while (getline(_xml_file,tmp))
        {
            _xml_data=_xml_data+tmp+'\n';
        }
    }

    XML_Tree tree;
    TreeNode* currentNode = nullptr;

    regex _tag_regex("<([^<>]+)>");
    sregex_iterator _tag_iterator(_xml_data.begin(),_xml_data.end(),_tag_regex);
    sregex_iterator _endtag_iterator; 

    while (_tag_iterator !=_endtag_iterator ) {
        std::smatch match = *_tag_iterator;
        string tag = match.str(1);

        // Check if this is a start tag or an end tag
        if(tag[1] != '/') // Start tag
        {
            string tag_name = tag.substr(1, tag.size() - 2); // Remove the angle brackets

            if(currentNode == nullptr) // If there is no current node, this is the root
            {
                tree.InsertRoot(tag, "");
                currentNode = tree.root;
            }
            else // Otherwise, this is a child node
            {
                tree.InsertChild(currentNode, tag, "");
                currentNode = currentNode->children.back();
            }
        }
        else // End tag
        {
            currentNode = currentNode->parent; // Move up to the parent node
        }

        ++_tag_iterator;
    }

    // Now you can use your tree
    // For example, print the tree using pre-order traversal
    tree.preOrderTraversal(tree.root);

    return 0;
}