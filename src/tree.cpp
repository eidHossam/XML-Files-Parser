#include "tree.h"

void XML_Tree::InsertRoot(string _tag_name, string _tag_data) {
  if (root == NULL) {
    root = TreeNode::GetNewNode(_tag_name, _tag_data);
  }
}

void XML_Tree::InsertChild(TreeNode * parent, string _tag_name, string _tag_data) {
  TreeNode * childNode = TreeNode::GetNewNode(_tag_name, _tag_data);
  childNode -> parent = parent; // Set the parent of the child node
  parent -> children.push_back(childNode);
}

void XML_Tree::preOrderTraversal() {
  preOrderTraversalHelper(this -> root);
}

void XML_Tree::preOrderTraversalHelper(TreeNode * node) {
  if (node == NULL)
    return;

  cout << node -> _tag_name << ": " << node -> _tag_data << endl;

  for (auto child: node -> children) {
    preOrderTraversalHelper(child);
  }
}