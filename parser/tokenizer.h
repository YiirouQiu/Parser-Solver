#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

struct Token
{
    std::string content;
    std::string type;
};

// a tokenzier breaks a stream of string into tokens
class Tokenizer
{
  std::string tokenLine;
  size_t currPosition;

  // your code starts here
  public:
    Tokenizer(std::string ln);

    // add two helper functions
    //define a helper function: input a string and a certain char, check whether the char is in string
    bool isInString(std::string str, std::string findChar);

    //define a helper function, check if the char is a valid variable.
    bool isValidVariable(char s);


    bool advanceToken(); // advance to the next token; return false if no more token exist
    bool hasToken() const; // check whether there is a current token
    Token getToken(); // returns the token being processed

    // can get curr token repeatedly
    Token repeatGetToken();

};

#endif
