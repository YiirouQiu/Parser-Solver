#ifndef TNODE_H
#define TNODE_H

#include <string>

// abstract superclass of the syntax tree node
class TreeNode {
    int ID = 0;
    std::string content;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;
  public:
    TreeNode(std::string cntt);
    TreeNode *getLeftChild() const;
    TreeNode *getRightChild() const;
    std::string getContent() const;
    int getID();
    //virtual bool evaluate(const std::map<std::string, bool> &assignment) const = 0; // pure virtual method
    void updateLeftChild(TreeNode *lChild); // for the operator "-", the operand is stored in leftChild
    void updateChildren(TreeNode *lChild, TreeNode *rChild);
    void updateID(int id);
    //std::string printStr() const; // debug method
    virtual ~TreeNode();

};

// concrete tree node of opertaor type
class OperatorNode : public TreeNode {
  public:
    OperatorNode(std::string cntt);
    //bool evaluate(const std::map<std::string, bool> &assignment) const override;
    // your code starts here
};

// concrete tree node of varibale type
class VariableNode : public TreeNode {
  public:
    VariableNode(std::string cntt);
    //bool evaluate(const std::map<std::string, bool> &assignment) const override;
    // your code starts here
};

#endif
