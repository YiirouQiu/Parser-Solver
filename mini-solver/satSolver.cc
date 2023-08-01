#include "satSolver.h"
//#include "minisat/core/SolverTypes.h"
//#include "minisat/core/Solver.h"
#include <memory>
#include <iostream>
/*
bool satCallingSolver(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // your code starts here
  bool result;
  satSolver solver = satSolver(numVar, cnf);
  result = solver.solve();
  return result;
}
*/

satSolver::satSolver(std::vector<std::vector<int>> &c): cnf{c} {};

bool satSolver::emptyClause () {
  for (std::vector<int> c : cnf) {
    if (c.empty()) {
      return true;
    }
  }
  return false;
}


bool satSolver::solve() {
  return DPLL(cnf, assignMap);
}

bool satSolver::DPLL (std::vector<std::vector<int>> &cnf, std::map<int, bool> &assignMap) {
  BCP(cnf, assignMap);
  if (cnf.empty()) {
    return true;
  } else if (emptyClause()) {
    return false;
  }
  int curVar = chooseVar();
  assignMap[curVar] = true;
  if (DPLL(cnf, assignMap)) {
    return true;
  } else {
    assignMap[curVar] = false;
    return DPLL(cnf, assignMap);
  }
}


void satSolver::BCP (std::vector<std::vector<int>> &cnf, std::map<int, bool> &assignMap) {
  std::map<int, bool>::iterator iter;
  std::vector<std::vector<int>>::iterator clause;
  for (iter = assignMap.begin(); iter != assignMap.end();iter++) {
    if (recordMap.count(iter->first) != 0) {continue;}
    recordMap[iter->first] = iter->second;
    for (clause = cnf.begin(); clause != cnf.end();) {
        if ((checkSign(*clause, iter->first) && (iter->second == true)) || 
        (checkSign(*clause, -1 * iter->first) && (iter->second == false))) {
          cnf.erase(clause);
        } else if ((checkSign(*clause, iter->first) && (iter->second == false)) || 
        (checkSign(*clause, -1 * iter->first) && (iter->second == true))) {
          if (iter->second == true) {removeVar(*clause,-1 * iter->first);}
          else {removeVar(*clause, iter->first);}
          //clause++;

          if (clause->size() == 1) {
          int lit = clause->at(0);
          if (lit > 0) {
            if (assignMap.find(lit) != assignMap.end() && assignMap.at(lit) == false) {errorChecking--;}
            assignMap[lit] = true;
          } else {
            if (assignMap.find(-lit) != assignMap.end() && assignMap.at(-lit) == true) {errorChecking--;}
            assignMap[-lit] = false;
          }
          cnf.erase(clause);
        } else {
          clause++;
        }

        } else {
           clause++;
        }
    }
  }
}


bool satSolver::checkSign(std::vector<int> c, int var) {
  for (int i : c) {
    if (i == var) {return true;}
  }
  return false;
}

int satSolver::chooseVar() {
  for (int i = 1; i < 1000; i++) {
    if (assignMap.find(i) == assignMap.end()) {
      return i;
    }
  }
  return 0;
}
  /*
  if (curVar < 0) {
    return -1 * curVar;
  } else {
    return curVar;
  }
  
  */

void satSolver::removeVar(std::vector<int> &c, int var) {
  std::vector<int>::iterator iter;
  for (iter = c.begin(); iter != c.end();) {
    if (var == *iter) {
      c.erase(iter);
    } else {
      iter++;
    }
  }
}

/*
satSolver::~satSolver() {
  cnf.clear();
}
*/
