#ifndef GRAPH_H
#define GRAPH_H

#include <stack>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <string>
#include "Rule.h"
#include "Predicate.h"

#include <iostream>

class Graph
{
private:
    std::map<int, std::set<int>> dependencyGraph;
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
                    if (p->GetId() == matchRule.first->GetHead()->GetId()) {
                        dependencies.insert(matchRule.second);
                    }
                }
            }

            dependencyGraph.insert(std::pair<int, std::set<int>>(index++, dependencies));
        }

    }

    std::string GetDependencyGraph() {
        std::stringstream os;

        for (std::pair<int, std::set<int>> dep : dependencyGraph) {
            os << dep.first << " : ";
            for (int i : dep.second) {
                os << i << ", ";
            }
            os << std::endl;
        }

        return os.str();
    }
};

#endif // GRAPH_H