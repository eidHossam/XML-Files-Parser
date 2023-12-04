#include <string.h>
#include<bits/stdc++.h> 
#include <list>


using namespace std;


// class TreeNode
// {
//      public:
//     /*datatypes of the tree*/
//     string _tag_name;
//     string _tag_data;
    
//     /*children of a node *children tags* */
//     vector<TreeNode*> children ;


//     friend class XML_Tree;

// };
// class XML_Tree
// {

    

//     public:
//     TreeNode * root=nullptr;
    
//     TreeNode* GetNewNode(string _tag_name , string _tag_data)
//     {
//         TreeNode* newNode= new TreeNode();
//         newNode->_tag_name=_tag_name;
//         newNode->_tag_data=_tag_data;
//         return newNode;
//     }
//     TreeNode* Insert(TreeNode* root,string _tag_name , string _tag_data)
//     {
//         if(root==nullptr)
//         {
//             root=GetNewNode(_tag_name,_tag_data);
//             return root;
//         }
//     }
    
//     void InsertRoot(string _tag_name , string _tag_data)
//     {
//         if(root == nullptr)
//         {
//             root = GetNewNode(_tag_name, _tag_data);
//         }
//         else
//         {
//             cout << "Root already exists." << endl;
//         }
//     }
    
//     void InsertChild(TreeNode* parent, string _tag_name , string _tag_data)
//     {
//         TreeNode* childNode = GetNewNode(_tag_name, _tag_data);
//         parent->children.push_back(childNode);
//     }
    
//     void preOrderTraversal(TreeNode *node)
//     {
//         if(node == nullptr)
//             return;
        
//         //Edit Here -------------------------------- ----------------------------------------------------
//         cout << node->_tag_name << ": " << node->_tag_data << endl;
        
//         for(auto child : node->children)
//         {
//             preOrderTraversal(child);
//         }
//     }
// };



class TreeNode
{
public:
    /*datatypes of the tree*/
    string _tag_name;
    string _tag_data;
    
    /*children of a node *children tags* */
    vector<TreeNode*> children;

    /*parent of a node*/
    TreeNode* parent = nullptr;

    friend class XML_Tree;
};

class XML_Tree
{
public:
    TreeNode * root=nullptr;
    
    TreeNode* GetNewNode(string _tag_name , string _tag_data)
    {
        TreeNode* newNode= new TreeNode();
        newNode->_tag_name=_tag_name;
        newNode->_tag_data=_tag_data;
        return newNode;
    }
    
    void InsertRoot(string _tag_name , string _tag_data)
    {
        if(root == nullptr)
        {
            root = GetNewNode(_tag_name, _tag_data);
        }
        else
        {
            cout << "Root already exists." << endl;
        }
    }
    
    void InsertChild(TreeNode* parent, string _tag_name , string _tag_data)
    {
        TreeNode* childNode = GetNewNode(_tag_name, _tag_data);
        childNode->parent = parent; // Set the parent of the child node
        parent->children.push_back(childNode);
    }
    
    void preOrderTraversal(TreeNode *node)
    {
        if(node == nullptr)
            return;
        
        cout << node->_tag_name << ": " << node->_tag_data << endl;
        
        for(auto child : node->children)
        {
            preOrderTraversal(child);
        }
    }
};




