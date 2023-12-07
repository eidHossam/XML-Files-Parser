#pragma once
#include<bits/stdc++.h> 
#include "TreeNode.h"

class XML_Tree
{
public:
    TreeNode * root = NULL;
    
    void InsertRoot(string _tag_name , string _tag_data);

    void InsertChild(TreeNode* parent, string _tag_name , string _tag_data);

    void preOrderTraversal();
    
    void preOrderTraversalHelper(TreeNode *node);
};
