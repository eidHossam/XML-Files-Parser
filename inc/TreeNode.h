#pragma once
#include<bits/stdc++.h> 

using namespace std;

class TreeNode
{
public:
    /*datatypes of the tree*/
    string _tag_name;
    string _tag_data;
    int _node_level;
    int index;
    static int index_counter;
    /*children of a node *children tags* */
    vector<TreeNode*> children;

    /*parent of a node*/
    TreeNode* parent;

    TreeNode(string tag_name, string tag_data);

    static TreeNode* GetNewNode(string _tag_name , string _tag_data);

    bool has_Brother();
    int brothers_size();
    bool is_Last_Child();
    int get_Index();


};
