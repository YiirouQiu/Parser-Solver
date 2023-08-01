#include "treeNode.h"

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const {
  // your code starts here
  return content;
}

TreeNode *TreeNode::getLeftChild() const {
  // your code starts here
  return leftChild;
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts here
  return rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
  // your code starts here
  leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  // your code starts here
  rightChild = rChild;
  leftChild = lChild;
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  std::string content = getContent();
  TreeNode* lchild = getLeftChild();
  TreeNode* rchild = getRightChild();
  bool result = false;
  if(content == "-"){
    result = !lchild->evaluate(assignment);
  }else if(content == "*"){
    result = lchild->evaluate(assignment) && rchild->evaluate(assignment);
  }else if(content == "+"){
    result = lchild->evaluate(assignment) || rchild->evaluate(assignment);
  }
  return result;
}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  std::string content = getContent();
  if(content == "1"){
    return true;
  }else{
    return false;
  }
}

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  std::string content = getContent();
  bool result;
  result = assignment.at(content);
  return result;
}

TreeNode::~TreeNode() {
  // your code starts here
  if(leftChild){delete leftChild;}
  if(rightChild){delete rightChild;}
}
