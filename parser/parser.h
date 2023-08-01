#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>

#include "tokenizer.h"

class TreeNode;
class Tokenizer;

// Parser for the Boolean Formula
class FormulaParser {
    Tokenizer *tknzr;
    TreeNode *parseFormula(); // parse non-terminal Formula in the grammar
    TreeNode *parseConjTerm(); // parse non-terminal ConjTerm in the grammar
    TreeNode *parseTerm(); // parse non-terminal Term in the grammar
  public:
    bool errorInvalidFormu = false;  //Error: invalid input
    FormulaParser(std::string ln);
    TreeNode *getTreeRoot(); // parse the Boolean formula and return the root node of the formula syntax tree
    ~FormulaParser();
};

// Parser for the Assignment
class AssignmentParser {
    Tokenizer *tknzr;
  public:
    bool errorInvalidAssign = false;  //Error: invalid input
    bool errorContracdicting = false;     //Error: contradicting assignment
    AssignmentParser(std::string ln);
    std::map<std::string, bool> parseAssignment();
    ~AssignmentParser();
};

#endif
