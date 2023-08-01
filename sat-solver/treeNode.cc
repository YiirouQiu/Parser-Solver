#include "treeNode.h"

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const { return content; }

TreeNode *TreeNode::getLeftChild() const { return leftChild; }
TreeNode *TreeNode::getRightChild() const { return rightChild; }
int TreeNode::getID(){
    return ID;
}

void TreeNode::updateLeftChild(TreeNode *lChild) { leftChild = lChild; }

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  leftChild = lChild;
  rightChild = rChild;
}

void TreeNode::updateID (int id) {
    ID = id;
}

/*
std::string TreeNode::printStr() const {
  if (!leftChild && !rightChild) return content;
  else if (content == "-") return ("(" + content + "(" + leftChild->printStr() + ")" + ")");
  else return ("(" + leftChild->printStr() + content + rightChild->printStr() + ")");
}
*/

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}




VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}



TreeNode::~TreeNode() {
  delete leftChild;
  delete rightChild;
}
