#include <string.h>
#include<bits/stdc++.h> 
#include <list>


using namespace std;


class TreeNode
{
    /*datatypes of the tree*/
    string _tag_name;
    string _tag_data;
    
    /*children of a node *children tags* */
    vector<TreeNode*> children ;


    friend class XML_Tree;

};
class XML_Tree
{
    TreeNode * root=nullptr;
    
    TreeNode* GetNewNode(string _tag_name , string _tag_data)
    {
        TreeNode* newNode= new TreeNode();
        newNode->_tag_name=_tag_name;
        newNode->_tag_data=_tag_data;
        //init children to null??
        return newNode;
    }
    void Insert( string _tag_name , string _tag_data)
    {
        
    }
     
    void postOrderTraversal(TreeNode *node)
    {
        
    
       
    }
    
    void preOrderTraversal(TreeNode *node)
    {
        
       
    }

};