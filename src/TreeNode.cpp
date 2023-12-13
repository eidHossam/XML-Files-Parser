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

TreeNode* TreeNode::GetNewNode(string _tag_name , string _tag_data)
{
    TreeNode* newNode= new TreeNode(_tag_name, _tag_data);
    return newNode;
}
