#include "TreeNode.h"
int TreeNode:: index_counter=0;
TreeNode::TreeNode(string tag_name, string tag_data){
    _tag_name = tag_name;
    _tag_data = tag_data;
    index=index_counter;
    index_counter++;
    _node_level = 0;
    visited=false; //it helps when traversing the tree to convert to json
    parent = NULL;
}

void TreeNode::preOrderTraversalUsersHelper(TreeNode * node ,vector<TreeNode*>& users ) {
    if (node == NULL)
        return;

    if (node->_tag_name=="user")
    {
        users.push_back(node);
    }
    

    for (auto child: node -> children) {
        preOrderTraversalUsersHelper(child,users);
    }
}

vector<TreeNode*> TreeNode::no_Of_Users_Vector()
{
    vector<TreeNode*> users;
    preOrderTraversalUsersHelper(this,users);
    return users;
}
vector <TreeNode*> TreeNode:: id_Of_Users()
{
    vector<TreeNode*> ids;
    vector<TreeNode*> users=this->no_Of_Users_Vector();
    for(auto var : users)
    {
        for(auto child : var->children)
        {
            if(child->_tag_name=="id")
            {     
                ids.push_back(child);
                break;
            }    
        }
    }
    return ids;

}
void TreeNode::preOrderTraversalfollowerIDHelper(TreeNode * node ,vector<string>& followerids ) {
    if (node == NULL)
        return;

    if (node->_tag_name=="follower")
    {
        followerids.push_back(node->children[0]->_tag_data);
    }
    

    for (auto child: node -> children) {
        preOrderTraversalfollowerIDHelper(child,followerids);
    }
}
vector<vector<string>> TreeNode::followersID()
{
   
    vector<TreeNode*> users=this->no_Of_Users_Vector();
  
    vector<vector<string>> followersids;
    

    vector<string> temp;
    int i=0;
    for(auto var : users)
    {

       preOrderTraversalfollowerIDHelper(var,temp);
       followersids.push_back(temp);
       temp.clear();
       i++;

    }
    return followersids;
}
bool TreeNode::has_Brother()
{
    if(parent==NULL)
    {
        return false;
    }
    if(parent->children.size()>1)
    {    
        return true;
    }
    return false;
}
int TreeNode:: get_Index()
{
    return index;
}


int TreeNode::brothers_size()
{
    int count=1;
    if(parent==NULL)
    {
        return count;
    }
    count=parent->children.size();
    return count;

}
bool TreeNode:: is_Last_Child()
{
    if(parent==NULL)
    {
        return true;
    }
    int size=brothers_size();
    if (index==parent->children[size-1]->index )
    {
        return true;
    }
    return false;
    
}
int TreeNode:: similar_Brothers()
{
    if(parent==NULL)
    {
        return 0;
    }
    int similar_brothers=0;
    int size=brothers_size();
    for (int i = 0; i < size; i++)
    {
        if (_tag_name==parent->children[i]->_tag_name && index !=parent->children[i]->index )
        {
          similar_brothers++;
        }
        
    }
    return similar_brothers;    

}
int TreeNode:: last_similarBrother_index()
{
    if(parent==NULL)
    {
        return 0;
    }
    int similar_brothers=0;
    int last_Similar_index=index;
    int size=brothers_size();
    for (int i = 0; i < size; i++)
    {
        if (_tag_name==parent->children[i]->_tag_name )
        {
          last_Similar_index=parent->children[i]->index;
        }
        
    }
    return last_Similar_index;
}
bool TreeNode:: is_Similar_Visited()
{
    if(parent==NULL)
    {
        return false;
    }
   
    int size=brothers_size();
    for (int i = 0; i < size; i++)
    {
        if(parent->children[i]->similar_Brothers())
        {
           
            return parent->children[i]->visited;
        }
    }
    return visited;
}

TreeNode* TreeNode::GetNewNode(string _tag_name , string _tag_data)
{
    TreeNode* newNode= new TreeNode(_tag_name, _tag_data);
    return newNode;
}
