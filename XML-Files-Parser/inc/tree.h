#pragma once
#include "TreeNode.h"

class XML_Tree
{
private:
    void preOrderTraversalHelper(TreeNode *node);
public:
    TreeNode * root;

    XML_Tree();
    
    void InsertRoot(string _tag_name , string _tag_data);

    void InsertChild(TreeNode* parent, string _tag_name , string _tag_data);

    void preOrderTraversal();
    
};
