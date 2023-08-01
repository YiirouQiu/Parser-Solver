#include "tseitinTransformer.h"
#include "satSolver.h"
#include <vector>
#include <iostream>
#include "parser.h"
#include "treeNode.h"


// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line) {
  int scPos = line.find(";");
  if (scPos != -1) throw "Error: invalid input";
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    
    std::string line; // store each input line
    // your code starts here
    std::getline(std::cin, line);
    if (std::cin.eof()) break; // terminate gracefully encountering eof
    try {
      parseLine(line);
    } catch (const char *e) {
      std::cout << e << std::endl;
      continue;
    }

    FormulaParser fParser{line};
    TreeNode *treeRoot = nullptr;
    bool result;
    try {
      treeRoot = fParser.getTreeRoot();
      TseitinTransformer tseitinTransformer = TseitinTransformer(treeRoot);
      std::vector<std::vector<int>> cnf;
      cnf = tseitinTransformer.transform();
      satSolver solver = satSolver(cnf);
      result = solver.solve();
      if (solver.errorChecking < 0) {result = false;}
      cnf.clear();
      } catch (const char *e) {
      delete treeRoot;
      std::cout << e << std::endl;
      continue;
    }
    if (result) std::cout << "sat" << std::endl;
    else std::cout << "unsat" << std::endl;
    delete treeRoot;
  }
}
