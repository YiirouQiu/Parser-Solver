#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"

FormulaParser::FormulaParser(std::string ln): tknzr {new Tokenizer{ln}} {}

TreeNode* FormulaParser::parseConjTerm() {
  // your code starts here
  Token tok;
  TreeNode* resultNode = nullptr; // initialize resultNode
  TreeNode* lchild = parseTerm(); // ConjTerm --> Term
  resultNode = lchild;

  while(tknzr->hasToken()){
    // make sure next token is not "+" or ")"
    tok = tknzr->repeatGetToken();
    if((tok.content == "+") || (tok.content == ")")){
      return resultNode;
    }

    // start get token
    tok = tknzr->getToken();
    if((tok.content == "*") && (tknzr->hasToken())){
      TreeNode* currNode = new OperatorNode(tok.content);
      TreeNode* rchild = parseConjTerm();
      currNode->updateChildren(lchild, rchild);
      resultNode = currNode;
      return resultNode;
    }else{
      errorInvalidFormu = true;
      return nullptr;
    }
  }
  return resultNode;
}

TreeNode* FormulaParser::parseTerm() {
  // your code starts here
  Token tok;
  TreeNode* resultNode = nullptr;
  
  while(tknzr->hasToken()){
    tok = tknzr->getToken();
    if(tok.type == "variable"){
      resultNode = new VariableNode(tok.content);
      return resultNode;
    }else if(tok.type == "constant"){
      resultNode = new ConstantNode(tok.content);
      return resultNode;
    }else if(tok.type == "operator"){
      if(tok.content == "+" || tok.content == "*"){
        errorInvalidFormu = true;  
        return resultNode;  // resultNode is nullptr;
      }else{  //means the operator is "-"
        resultNode = new OperatorNode(tok.content);
        if(!tknzr->hasToken()){
          errorInvalidFormu = true; // there should be a variable or value after "-"
          return nullptr;
        }
        TreeNode* lchild = parseTerm(); //Grammar: Term --> "-" Term
        resultNode->updateLeftChild(lchild);
        return resultNode;
      }
    }else if(tok.content == "("){
      resultNode = parseFormula();
      if(!tknzr->hasToken()){
        errorInvalidFormu = true; // there should be a ")" after "("
        return nullptr;
      }

      tok = tknzr->getToken();  // get the right parenthese.
       // avoid "()" situation, and make sure there is a ")" after "(".
      if(resultNode == nullptr || (tok.content != ")")){
        errorInvalidFormu = true; //content type is not a ")" or the expression is like ()
        return nullptr;
      }
      return resultNode;
    }else{
      errorInvalidFormu = true; // else error
      return nullptr;
    }
  }
  return resultNode;
}

TreeNode *FormulaParser::parseFormula() {
  // your code starts here
  Token tok;
  TreeNode* resultNode = nullptr;
  TreeNode* lchild = parseConjTerm();  //Grammar: Formula --> ConjTerm()
  resultNode  = lchild;

  while(tknzr->hasToken()){
    // make sure next token is not ")"
    tok = tknzr->repeatGetToken();
    if(tok.content == ")"){
      return resultNode;
    }

    // start get token
    tok = tknzr->getToken();

    if(tok.content == "+" && tknzr->hasToken()){
      TreeNode* currNode = new OperatorNode(tok.content);
      TreeNode* rchild = parseFormula();  //Grammar: Formula --> ConjTerm() "+" Formula()
      currNode->updateChildren(lchild, rchild);
      resultNode = currNode;
      return resultNode;
    }else{
      errorInvalidFormu = true;
      return nullptr;
    }
  }
  return resultNode;
}

TreeNode * FormulaParser::getTreeRoot() {
  // your code starts here
  return parseFormula();
}

FormulaParser::~FormulaParser() {
  // your code starts here
  if(tknzr){delete tknzr;}
}

AssignmentParser::AssignmentParser(std::string ln): tknzr {new Tokenizer{ln}} {}

std::map<std::string, bool> AssignmentParser::parseAssignment() {
  std::map<std::string, bool> results;
  // your code starts here
  Token varName;
  Token splitColon;
  Token varValue;
  Token comma;

  while(tknzr->hasToken()){

    // check the variable form is var:value.
    varName = tknzr->getToken();
    if(!(varName.type == "variable") || !(tknzr->hasToken()) || !(tknzr->advanceToken())){
      errorInvalidAssign = true; // variable type or variable has/advance token missing
      break;
    }
    splitColon = tknzr->getToken();
    varValue = tknzr->getToken();

    // check the types of constant/colon
    if((splitColon.content != ":") || (varValue.type != "constant")){
      errorInvalidAssign = true; //colon missing or value is not 0 or 1
      break;
    }
    
    // check repeat value in map, check situation: 1 * Var; Var:1, Var:1 (true)
    if(results.count(varName.content)){
      if(((results.at(varName.content) == 1) && varValue.content == "0") 
      || ((results.at(varName.content) == 0) && varValue.content == "1")){
        errorContracdicting = true;
        break;
      }
    }

    // tok comma
    if(tknzr->hasToken()){
      comma = tknzr->getToken();
      // original condition to check the "," : (comma.type != "skipChar_comma") || (!tknzr->hasToken())
      if(comma.type != "skipChar_comma"){
        errorInvalidAssign = true;  //comma type wrong or has a comma but does not have a value after comma
        break;
      }
    }
    // check the length of variable
    int length = varName.content.length();
    if(length > 10){
      errorInvalidAssign = true;
    }

    //define the name:value in results
    if(varValue.content == "1"){
      results[varName.content] = true; 
    }else if(varValue.content == "0"){
      results[varName.content] = false; 
    }

  }
  return results;
}

AssignmentParser::~AssignmentParser() {
  // your code starts here
  if(tknzr){delete tknzr;}
}
