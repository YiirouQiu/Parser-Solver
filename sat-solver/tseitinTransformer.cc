#include "tseitinTransformer.h"

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
  int curID = varIdCounter;
  varIdCounter++;
  subRoot->updateID(curID);
  std::string content = subRoot->getContent();
  if (content == "-") {
    int childID = transSubformula(subRoot->getLeftChild());
    addNegEq(curID, childID);
  } else if (content == "*") {
    int leftID = transSubformula(subRoot->getLeftChild());
    int rightID = transSubformula(subRoot->getRightChild());
    addAndEq(curID, leftID, rightID);
  } else if (content == "+") {
    int leftID = transSubformula(subRoot->getLeftChild());
    int rightID = transSubformula(subRoot->getRightChild());
    addOrEq(curID, leftID, rightID);
  } else {
    if (varIdTable.find(content) == varIdTable.end()) {
      varIdTable[content] = curID;
    } else {
      curID = varIdTable[content];
      varIdCounter--;
    }
  }
  return curID;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
  // curr <-> -child  === [curr, child] [-curr, -child]
  std::vector<int> currVector1, currVector2;

  currVector1.push_back(curID);
  currVector1.push_back(childID);
  cnf.push_back(currVector1);

  currVector2.push_back(-1 * curID);
  currVector2.push_back(-1 * childID);
  cnf.push_back(currVector2);
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  // curr <-> left + right === [-curr, left, right] [curr, -left] [curr, -right]
  std::vector<int> currVector1, currVector2, currVector3;

  currVector1.push_back(-1 * curID);
  currVector1.push_back(leftID);
  currVector1.push_back(rightID);
  cnf.push_back(currVector1);

  currVector2.push_back(curID);
  currVector2.push_back(-1 * leftID);
  cnf.push_back(currVector2);

  currVector3.push_back(curID);
  currVector3.push_back(-1 * rightID);
  cnf.push_back(currVector3);
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  // curr <-> left * right === [-curr, left] [-curr, right] [curr, -left, -right]
  std::vector<int> currVector1, currVector2, currVector3;

  currVector1.push_back(curID);
  currVector1.push_back(-1 * leftID);
  currVector1.push_back(-1 * rightID);
  cnf.push_back(currVector1);

  currVector2.push_back(-1 * curID);
  currVector2.push_back(leftID);
  cnf.push_back(currVector2);

  currVector3.push_back(-1 * curID);
  currVector3.push_back(rightID);
  cnf.push_back(currVector3);
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  transSubformula(formulaRoot);
  varIdCounter--;
  std::vector<int> rootVec;
  rootVec.push_back(formulaRoot->getID());
  cnf.push_back(rootVec);
  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  // your code starts here
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return varIdCounter;
}
