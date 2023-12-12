#include "XML_to_json.h"



XML_to_json::XML_to_json( XML_Parser parser) {
  xml_Data=parser.get_original_xml_data();
  file_tree_json=parser.build_xml_tree();
    
}
void XML_to_json::preOrderTraversalVectorFill(TreeNode * node) {
    
  if (node == NULL)
    return;

  //cout << node -> _tag_name << ": " << node -> _tag_data << endl;
  tree_Nodes.push_back(node);

  for (auto child: node -> children) {
    preOrderTraversalVectorFill(child);
  }
}

// void XML_to_json:: printLevelOrder(TreeNode* root)
// {
//     // Base Case
//     if (root == NULL)
//         return;
 
//     // Create an empty queue for level order traversal
//     queue<TreeNode*> q;
 
//     // Enqueue Root and initialize height
//     q.push(root);
 
//     while (q.empty() == false) {
         
//         // Print front of queue and remove it from queue
//         TreeNode* node = q.front();
//         //cout << node->_tag_name << " ";
//         //cout << node->_tag_data << " ";
//         tree_Nodes.push_back(node);

//         q.pop();
 
//         // Enqueue left child
//         for (auto child: node -> children) {
//             q.push(child);
//         }
       
//     }
// }
string XML_to_json:: json_string()
{
    json_output="{\n";
    if(file_tree_json->root==nullptr)
    {
      json_output+="}";
      return json_output;
    }
    preOrderTraversalVectorFill(file_tree_json->root);
    int counter=0;
    while(!tree_Nodes.empty())
    {
      string key="\""+tree_Nodes[counter]->_tag_name+"\"";
      string value="\""+tree_Nodes[counter]->_tag_data+"\"";
      json_output+=key+":"+value+",\n";
      counter++;

    }
    return json_output;

}