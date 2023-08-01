#include "tokenizer.h"


Tokenizer::Tokenizer(std::string ln):tokenLine(ln) {
  // complete the constructor
  // tokenLine = ln;
  // initialize position and tokenLine
  currPosition = 0;
}

bool Tokenizer::advanceToken() {
  // your code starts here
  if(!hasToken()){
    return false;
  }
  size_t varLength = 1;
  while(isValidVariable(tokenLine[currPosition + varLength])){
    varLength++;
  }
  if(tokenLine[currPosition + varLength]){
    return true;
  }
  return false;
}

bool Tokenizer::hasToken() const {
  // your code starts here
    if(tokenLine[currPosition]){
    return true;
  }
  return false;
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() {
  Token resultToken;
  // your code starts there
  bool gotToken = false;
    while(!gotToken){
    gotToken = true;
    std::string curr;
    curr = tokenLine[currPosition];
    if(isValidVariable(tokenLine[currPosition])){
      std::string var = "";
      while(isValidVariable(tokenLine[currPosition]) || isInString("0123456789", curr)){
        var += tokenLine[currPosition];
        currPosition++;
        curr = tokenLine[currPosition];
      }
      resultToken.content = var;
      resultToken.type = "variable";
      break;
    }

    if(isInString("+-*", curr)){
      resultToken.content = curr;
      resultToken.type = "operator";
    }else if(curr == "("){
      resultToken.content = curr;
      resultToken.type = "leftP";
    }else if(curr == ")"){
      resultToken.content = curr;
      resultToken.type = "rightP";
    }else if(isInString(":", curr)){
      resultToken.content = curr;
      resultToken.type = "skipChar_colon";
    }else if(isInString(",", curr)){
      resultToken.content = curr;
      resultToken.type = "skipChar_comma";
    }else if(isInString("01", curr)){
      resultToken.content = curr;
      resultToken.type = "constant";
    }else{
        resultToken.content = curr;
        resultToken.type = "unknown";
    }
    currPosition++;
  }
  return resultToken;
}

Token Tokenizer::repeatGetToken(){
  Token resultToken;
  size_t tmpPosition = currPosition;
  bool gotToken = false;
    while(!gotToken){
    gotToken = true;
    std::string curr;
    curr = tokenLine[tmpPosition];
    if(isValidVariable(tokenLine[tmpPosition])){
      std::string var = "";
      while(isValidVariable(tokenLine[tmpPosition]) || isInString("0123456789", curr)){
        var += tokenLine[tmpPosition];
        tmpPosition++;
      }
      resultToken.content = var;
      resultToken.type = "variable";
      break;
    }

    if(isInString("+-*", curr)){
      resultToken.content = curr;
      resultToken.type = "operator";
    }else if(curr == "("){
      resultToken.content = curr;
      resultToken.type = "leftP";
    }else if(curr == ")"){
      resultToken.content = curr;
      resultToken.type = "rightP";
    }else if(isInString(":", curr)){
      resultToken.content = curr;
      resultToken.type = "skipChar_colon";
    }else if(isInString(",", curr)){
      resultToken.content = curr;
      resultToken.type = "skipChar_comma";
    }else if(isInString("01", curr)){
      resultToken.content = curr;
      resultToken.type = "constant";
    }else{
        resultToken.content = curr;
        resultToken.type = "unknown";
    }
    //currPosition++;
  }
  return resultToken;
}


// two helper functions
bool Tokenizer::isInString(std::string str, std::string findChar){
    if((str.find(findChar) != std::string::npos)){
        return true;
    }else{
        return false;
    }
}

bool Tokenizer::isValidVariable(char s){
    if (!(s >= 65 && s <= 90) && !(s >= 97 && s <= 122)) {
        return false;
    }
    return true;
}


