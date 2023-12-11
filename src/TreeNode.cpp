#include "TreeNode.h"

TreeNode::TreeNode(string tag_name, string tag_data){
    _tag_name = tag_name;
    _tag_data = tag_data;
    parent = NULL;
}

TreeNode* TreeNode::GetNewNode(string _tag_name , string _tag_data)
{
    TreeNode* newNode= new TreeNode(_tag_name, _tag_data);
    return newNode;
}
   