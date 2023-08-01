#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"

// a helper function to remove all the spaces in the "line" string;
std::string removeSpaces(const std::string &line, std::string removedChar = " "){
  size_t charPosition;
  size_t charLength = removedChar.length();
  std::string formattedLine = line;
  while((charPosition = formattedLine.find(removedChar)) != std::string::npos){
    // erase the spaces.
    formattedLine = formattedLine.erase(charPosition, charLength);
  }
  return formattedLine;
}

// a helper function to remove whitespace from beginning and end of string
std::string removeBegEndSpace(std::string& str){
    int length = str.length();
    if(str[0] == ' '){
        str = str.substr(1);
        return removeBegEndSpace(str);
    }
    if(str.back() == ' '){
        str = str.substr(0, length - 1);
        return removeBegEndSpace(str);
    }
    return str;
}

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr) {
  std::string formattedLine = line, splitChar = ";";
  size_t charPosition = formattedLine.find(splitChar);
  size_t charLength = splitChar.length();
  formulaStr = formattedLine.substr(0, charPosition);
  assignmentStr = formattedLine.substr(charPosition+charLength);
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    // your code starts here

    //read the input line.
    std::getline(std::cin, line);

    //terminate gracefully (and quietly) once it sees EOF
    if(std::cin.eof()){
      break;
    }

    //STEP 1: remove all the spaces in line
    std::string originalLine = line;
    //std::string originalFormulaStr, originalAssignmentStr;
    line = removeSpaces(line);

    //Error checking 1: check if there is a ";" in line
    if(line.find(";") == std::string::npos){
      std::cout << "Error: invalid input" << std::endl;
      continue;
    }

    //STEP 2: get the seperate formula line and assignment line
    parseLine(line, formulaStr, assignmentStr);
    //parseLine(originalLine, originalFormulaStr, originalAssignmentStr); // used for white space error checking

    //Error checking 2: check empty input formula string
    if(formulaStr == ""){
      std::cout << "Error: invalid input" << std::endl;
      continue;
    }

    //STEP 3: do formula parser, to get a parser tree
    FormulaParser formula(formulaStr);
    TreeNode* finalTree;
    finalTree = formula.getTreeRoot();

    //STEP 4: do assignment parser, get an assignment map
    AssignmentParser assignment(assignmentStr);
    std::map<std::string, bool> assignMap = assignment.parseAssignment();



    //Error checking 3: detect errors in parser or tokenizer //"INVALID INPUT" part//

    //error checking
    Tokenizer* tokenTestError;
    Token tokTestError;
    bool errorInvalidParenthese = false;
    bool errorInvalidVarLength = false;
    bool errorInvalidVarSpace = false;

    bool errorIncomplete = false;

    //Error checking 3.1: check parentheses error situation 
    //Error checking 3.2: check variable length (in formyla) sitiuation 
    int cnt = 0, varLength;
    tokenTestError = new Tokenizer(formulaStr);
    while(tokenTestError->hasToken()){
      tokTestError = tokenTestError->getToken();
      if(tokTestError.content == "("){
        cnt++;
      }else if(tokTestError.content == ")"){
        cnt--;
      }else if(tokTestError.type == "variable"){
        varLength = tokTestError.content.length();
        if(varLength > 10){errorInvalidVarLength = true;}
      }
      if(cnt < 0){
        errorInvalidParenthese = true;
      }
    }

    // Error checking 3.3: check if there's any white space in variables
    std::string curr, numbers = " 1234567890", var = "";
    int i = 0, length = originalLine.length();
    while(i < length){
      curr = originalLine[i];
      if((originalLine[i] >= 65 && originalLine[i] <= 90) || (originalLine[i] >= 97 && originalLine[i] <= 122)){
        while((originalLine[i] >= 65 && originalLine[i] <= 90) || (originalLine[i] >= 97 && originalLine[i] <= 122) 
        || (numbers.find(curr) != std::string::npos)){
          var += curr;
          i++;
          curr = originalLine[i];
        }
        var = removeBegEndSpace(var);
        if(var.find(' ') != std::string::npos){
          errorInvalidVarSpace = true;
          break;
        }
        var = "";
      }
      i++;
    }
    

    //Error checking 5: check assignment incomplete situation
    tokenTestError = new Tokenizer(formulaStr);
    while(tokenTestError->hasToken()){
      tokTestError = tokenTestError->getToken();
      if(tokTestError.type == "variable"){
        if(!assignMap.count(tokTestError.content)){
          errorIncomplete = true;
          break;
        }
      }
    }


    if(formula.errorInvalidFormu || assignment.errorInvalidAssign || errorInvalidVarSpace 
    || errorInvalidParenthese || errorInvalidVarLength){
      std::cout << "Error: invalid input" << std::endl;
      delete finalTree;
      continue;
    }

    // Error checking 4: check contradicting assignment situation
    if(assignment.errorContracdicting){
      std::cout << "Error: contradicting assignment" << std::endl;
      delete finalTree;
      continue;
    }

    if(errorIncomplete){
      std::cout << "Error: incomplete assignment" << std::endl;
      delete finalTree;
      continue;
    }


    // STEP 5: evaluate, get the root value
    std::cout << finalTree->evaluate(assignMap) << std::endl;
    delete finalTree;

  }
}
