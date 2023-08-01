#ifndef SAT_H
#define SAT_H

#include <vector>
#include <map>

//bool satCallingSolver(unsigned int numVar, std::vector<std::vector<int>> &cnf); // return the SAT result of cnf by calling MiniSAT

class satSolver {
    std::map<int, bool> assignMap;
    std::vector<std::vector<int>> cnf;
    

    public:
    int errorChecking = 0;
    std::map<int, bool> recordMap;
    satSolver(std::vector<std::vector<int>> &cnf);
    bool emptyClause();
    bool solve();
    bool DPLL (std::vector<std::vector<int>> &cnf, std::map<int, bool> &assignMap);
    void BCP (std::vector<std::vector<int>> &cnf, std::map<int, bool> &assignMap);
    int chooseVar ();
    bool checkSign(std::vector<int> c, int var);
    void removeVar(std::vector<int> &c, int var);
    //~satSolver();

};

#endif
