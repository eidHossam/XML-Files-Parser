#include <string.h>
#include<bits/stdc++.h> 
#include <list>


using namespace std;


class TreeNode
{
public:
    /*datatypes of the tree*/
    string _tag_name;
    string _tag_data;
    
    /*children of a node *children tags* */
    vector<TreeNode*> children;

    /*parent of a node*/
    TreeNode* parent = NULL;

    friend class XML_Tree;
};


class XML_Tree
{
public:
    TreeNode * root = NULL;
    
    TreeNode* GetNewNode(string _tag_name , string _tag_data);
    
    void InsertRoot(string _tag_name , string _tag_data);

    void InsertChild(TreeNode* parent, string _tag_name , string _tag_data);

    void preOrderTraversal(TreeNode *node);
};
