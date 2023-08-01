#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <memory>


bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // your code starts here
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
  Minisat::vec<Minisat::Lit> varVector;
  bool result;

  for (unsigned int i = 0; i < numVar; i++) {
    Minisat::Lit a = Minisat::mkLit(solver->newVar());
    varVector.push(a);
  }

  for (std::vector<int> c : cnf) {
    Minisat::vec<Minisat::Lit> clause;
    for (int i : c) {
      if (i > 0) {
          Minisat::Lit curLit = varVector[i - 1];
          clause.push(curLit);
      } else {
        Minisat::Lit curLit = varVector[-i - 1];
        clause.push(~curLit);
      }
    }
    solver->addClause(clause);
    clause.clear();
  }

  result = solver->solve();
  varVector.clear();
  solver.reset(new Minisat::Solver());
  return result;
}
