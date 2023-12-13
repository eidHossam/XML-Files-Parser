#include "TreeNode.h"
int TreeNode:: index_counter=0;
TreeNode::TreeNode(string tag_name, string tag_data){
    _tag_name = tag_name;
    _tag_data = tag_data;
    index=index_counter;
    index_counter++;
    _node_level = 0;
    parent = NULL;
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
    if (_tag_name==parent->children[size-1]->_tag_name && _tag_data==parent->children[size-1]->_tag_data)
    {
        return true;
    }
    return false;
    
}

TreeNode* TreeNode::GetNewNode(string _tag_name , string _tag_data)
{
    TreeNode* newNode= new TreeNode(_tag_name, _tag_data);
    return newNode;
}
