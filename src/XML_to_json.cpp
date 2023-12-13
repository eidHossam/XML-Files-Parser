#include "XML_to_json.h"



XML_to_json::XML_to_json( XML_Parser parser) {
  xml_Data=parser.get_original_xml_data();
  file_tree_json=parser.build_xml_tree();
    
}
void XML_to_json::preOrderTraversalVectorTagsFill(TreeNode * node) {
    
  if (node == NULL)
    return;

  //cout << node -> _tag_name << ": " << node -> _tag_data << endl;
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

void XML_to_json:: json_string_builder(TreeNode * node)
{
  if (file_tree_json->root==nullptr)
  {
    json_output_string="";
    return ;
  }
  if (node == NULL)
  {
    return ;
  }
  string key="\""+node->_tag_name+"\"";
  string value="\""+node->_tag_data+"\"";
  
  if(!node->children.empty())
  {
    json_output_string+=tabs(node->_node_level);
    json_output_string+=key+":{\n";
  }
  else
  {
    json_output_string+=tabs(node->_node_level);
    json_output_string+=key+":"+value;
    
    if(node->is_Last_Child())
    {
      json_output_string+="\n";
    }
    else
    {
      json_output_string+=",\n";
    }
    
  }
  for (auto child: node -> children) 
  {
    json_string_builder(child);
  }
  if(!node->children.empty())
  {
    json_output_string+=tabs(node->_node_level)+"}";
    if(node->is_Last_Child())
    {
      json_output_string+="\n ";
    }
    else
    {
      json_output_string+=",\n ";
    }

  }

}

string XML_to_json::json_string()
{
  json_string_builder(file_tree_json->root);
  json_output_string="{\n"+json_output_string+"\n}";
  return json_output_string;
}