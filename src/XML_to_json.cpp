#include "XML_to_json.h"



XML_to_json::XML_to_json( XML_Parser parser) {
  xml_Data=parser.get_original_xml_data();
  file_tree_json=parser.build_xml_tree();
    
}
void XML_to_json::preOrderTraversalVectorTagsFill(TreeNode * node) {
    
  if (node == NULL)
    return;

  tree_Nodes.push_back(node);
  for (auto child: node -> children) {
    preOrderTraversalVectorTagsFill(child);
  }
}



string XML_to_json :: tabs(int level)
{
  string tabs;
  for (int i = 0; i < level+1; i++)
  {
    tabs+="\t";
  }
  return tabs;
}
void XML_to_json:: put_comma(TreeNode* node)
{
  if(node->is_Last_Child())
  {
    json_output_string+="\n";
  }
  else
  { 
    json_output_string+=",\n";
  }
}
void XML_to_json:: objectsArray_Style_Nested(TreeNode* node,string key,string value)
{
  if (!node->is_Similar_Visited())
  {
    json_output_string+=tabs(node->_node_level)+key+":[\n"+tabs(node->_node_level)+"{\n";
    node->visited=true;
    
  }
  else
  {
    json_output_string+=tabs(node->_node_level);
    json_output_string+="{\n";
  }
      
      
 // node->visited=true;
}
void XML_to_json:: objects_Style_Nested(TreeNode* node,string key,string value)
{
  json_output_string+=tabs(node->_node_level);
  json_output_string+=key+":{\n";
}
void XML_to_json:: objectsArray_Style_Leaf(TreeNode* node,string key,string value)
{
    if (!node->is_Similar_Visited())
    {
      json_output_string+=tabs(node->_node_level)+key+":[\n"+tabs(node->_node_level)+value;
      node->visited=true;
  
    }
    else
    {
      json_output_string+=tabs(node->_node_level);
      json_output_string+=value;
    }
      
}
void XML_to_json:: objects_Style_Leaf(TreeNode* node,string key,string value)
{
  json_output_string+=tabs(node->_node_level);
  json_output_string+=key+":"+value;
}
void XML_to_json:: closeBrackets_objectsArray_Style_Nested(TreeNode* node,string key,string value)
{
  if (node->index == node->last_similarBrother_index())
      {
        json_output_string+=tabs(node->_node_level)+"}\n"+tabs(node->_node_level)+"]";

      }
      else
      {
        json_output_string+=tabs(node->_node_level)+"}";

      }
}
void XML_to_json:: closeBrackets_objects_Style_Nested(TreeNode* node,string key,string value)
{
  json_output_string+=tabs(node->_node_level)+"}";

}
void XML_to_json:: closeBrackets_objectsArray_Style_Leaf(TreeNode* node,string key,string value)
{
  if(node->similar_Brothers() &&  node->index == node->last_similarBrother_index())
  {
    json_output_string+=tabs(node->_node_level)+"]\n";
  }
}
void XML_to_json:: json_string_builder(TreeNode * node)
{
  
  if (file_tree_json->root==nullptr)
  {
    json_output_string="";
    return ;
  }
  if (node == nullptr)
  {
    json_output_string="";
    return ;
  }
  
  string key="\""+node->_tag_name+"\"";
  string value="\""+node->_tag_data+"\"";
  
  if(!node->children.empty())
  {
    /*if nested nodes "tags"*/
    if (node->similar_Brothers())
    {
      objectsArray_Style_Nested(node,key,value);
    }
    else
    {
      objects_Style_Nested(node,key,value);
    }
    
    
  }
  else
  {
    /*if leaf nodes "tags"*/
    if (node->similar_Brothers())
    {
      objectsArray_Style_Leaf(node,key,value);
    }
    else
    {
      objects_Style_Leaf(node,key,value);
    }
    put_comma(node); 
  }

  /*recursive part on all nodes of the tree in a preorder style*/
  for (auto child: node -> children) 
  {
    json_string_builder(child);
  }

  /*this part is for putting the close brackets */
  if(!node->children.empty())
  {
    /*if nested nodes "tags"*/
    if (node->similar_Brothers())
    {
      /*if array of objects*/
      
      closeBrackets_objectsArray_Style_Nested(node,key,value);
    }
    else
    {
      /*if objects*/
      closeBrackets_objects_Style_Nested(node,key,value);

    }


    put_comma(node);


  }
  else
  {
    closeBrackets_objectsArray_Style_Leaf( node, key, value);
  }

}
 
string XML_to_json::json_string()
{
  json_string_builder(file_tree_json->root);
  json_output_string="{\n"+json_output_string+"\n}";
  return json_output_string;
}