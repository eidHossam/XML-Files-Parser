#include "tree.h"

TreeNode* XML_Tree::GetNewNode(string _tag_name , string _tag_data)
{
    TreeNode* newNode= new TreeNode();
    newNode->_tag_name=_tag_name;
    newNode->_tag_data=_tag_data;
    return newNode;
}

void XML_Tree::InsertRoot(string _tag_name , string _tag_data)
{
    if(root == NULL)
    {
        root = GetNewNode(_tag_name, _tag_data);
     }
    else
    {
        cout << "Root already exists." << endl;
    }
}

void XML_Tree::InsertChild(TreeNode* parent, string _tag_name , string _tag_data)
{
    TreeNode* childNode = GetNewNode(_tag_name, _tag_data);
    childNode->parent = parent; // Set the parent of the child node
    parent->children.push_back(childNode);
 }

// void XML_Tree::preOrderTraversal(TreeNode *node)
// {
//     if(node == NULL)
//         return;
    
//      cout << node->_tag_name << ": " << node->_tag_data << endl;
    
//     preOrderTraversal(child);
// }