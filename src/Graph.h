#ifndef GRAPH_H
#define GRAPH_H

#include <stack>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "Rule.h"
#include "Predicate.h"

#include <iostream>

class Graph
{
private:
    std::map<int, std::set<int>> dependencyGraph;
    std::map<int, std::set<int>> reverseDependencyGraph;
    std::map<int, int> reversePostOrder;
    std::map<int, int> postOrder;

    std::vector<int> visitedNodes;
    int currentIndex = 0;
public:
    void BuildDependencyGraph(std::vector<Rule*> rules) {
        std::map<Rule*, int> rulesIndices;
        int index = 0;

        for (Rule* r : rules) {
            rulesIndices.insert(std::pair<Rule*, int>(r, index++));
        }

        index = 0;
        for (std::pair<Rule*, int> currentRule : rulesIndices) {
            std::vector<Predicate*> preds = currentRule.first->GetBody();
            std::set<int> dependencies;

            for (Predicate* p : preds) {
                for (std::pair<Rule*, int> matchRule : rulesIndices) {
                    if (p->GetId() == matchRule.first->GetHead()->GetId() && index != matchRule.second) {
                        dependencies.insert(matchRule.second);
                    }
                }
            }

            dependencyGraph.insert(std::pair<int, std::set<int>>(index++, dependencies));
        }
    }

    void BuildReverseDependencyGraph() {
        for (std::pair<int, std::set<int>> depPair : dependencyGraph) {
            std::set<int> reverseDeps;
            reverseDependencyGraph.insert(std::pair<int, std::set<int>>(depPair.first, reverseDeps));
        }

        int index = 0;
        for (std::pair<int, std::set<int>> depPair : dependencyGraph) {
            std::set<int> reverseDeps;
            for (int dep : depPair.second) {
                reverseDependencyGraph.at(dep).insert(index);
            }

            index++;
        }
    }

    void TraverseReverse(int vertex) {
        visitedNodes.push_back(vertex);
        for (int dep : reverseDependencyGraph.at(vertex)) {
            if (std::find(visitedNodes.begin(), visitedNodes.end(), dep) == visitedNodes.end()) {
                TraverseReverse(dep);
            }
        }
        reversePostOrder.insert(std::pair<int, int>(currentIndex++, vertex));

        return;
    }

    std::map<int, int> GetReversePostOrder() {
        return reversePostOrder;
    }

    std::map<int, int> GetPostOrder() {
        return postOrder;
    }

    void ResetClock() {
        currentIndex = 0;
        visitedNodes.clear();
    }

    void TraverseOriginal(int vertex) {
        visitedNodes.push_back(vertex);
        for (int dep : dependencyGraph.at(vertex)) {
            if (std::find(visitedNodes.begin(), visitedNodes.end(), dep) == visitedNodes.end()) {
                TraverseOriginal(dep);
            }
        }
        postOrder.insert(std::pair<int, int>(currentIndex++, vertex));
        return;
    }

    std::string PrintDependencyGraph() {
        std::stringstream os;

        for (std::pair<int, std::set<int>> dep : dependencyGraph) {
            os << "R" << dep.first << ":";
            for (int i : dep.second) {
                os << "R" << i;
                auto it = dep.second.end();
                it--;
                if (i != *it) os << ",";
            }
            os << std::endl;
        }

        return os.str();
    }

    std::string PrintReverseDependencyGraph() {
        std::stringstream os;

        for (std::pair<int, std::set<int>> dep : reverseDependencyGraph) {
            os << "R" << dep.first << ":";
            for (int i : dep.second) {
                os << "R" << i;
                auto it = dep.second.end();
                it--;
                if (i != *it) os << ",";
            }
            os << std::endl;
        }

        return os.str();
    }

    std::string PrintReversePostOrder() {
        std::stringstream os;

        for (std::pair<int, int> ord : reversePostOrder) {
            os << ord.first << ": " << ord.second << std::endl;
        }

        return os.str();
    }

    std::map<int, std::set<int>> GetReverseDependencyGraph() {
        return reverseDependencyGraph;
    }
};

#endif // GRAPH_H