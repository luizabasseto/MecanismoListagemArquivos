#include "search.hpp"
#include <iostream>
#include <algorithm>

QueryProcessor::QueryProcessor(const Index& idx) : index(idx) {}

std::set<int> QueryProcessor::intersection(const std::vector<std::string>& termos) {

    if (termos.empty()) {
        return {};
    }
    std::set<int> r = index.getArchivesPerWords(termos[0]);

    for (size_t i = 1; i < termos.size(); ++i) {
        if (r.empty()) {
            return {};
        }

        std::set<int> atual = index.getArchivesPerWords(termos[i]);
        std::set<int> temp;
        
        auto it1 = r.begin();
        auto it2 = atual.begin();
        while (it1 != r.end() && it2 != atual.end()) {
            if (*it1 < *it2) {
                ++it1;
            } else if (*it2 < *it1) {
                ++it2;
            } else {
                temp.insert(*it1);
                ++it1;
                ++it2;
            }
        }
        r = temp;
    }

    return r;
}

std::vector<std::string> QueryProcessor::searches(std::vector<std::string>& consulta) {
    std::vector<std::string> nomesArquivos;

    std::set<int> findIds = intersection(consulta);

    for (int id : findIds) {
        std::string nome = index.getNameArchivesPerId(id);
        nomesArquivos.push_back(nome);
    }
    
    return nomesArquivos;
}