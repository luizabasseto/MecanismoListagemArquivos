#include "search.hpp"
#include <iostream>
#include <algorithm>

QueryProcessor::QueryProcessor(const Index& idx) : index(idx) {}

//faz a interseção dos documentos que contém a lista de palavras (termos)
std::set<int> QueryProcessor::intersection(const std::vector<std::string>& termos) {

    //retorna se nao tem termos para buscar
    if (termos.empty()) {
        return {};
    }
    //começa pela "palavra 1" da lista passada
    std::set<int> r = index.getArchivesPerWords(termos[0]);

    for (size_t i = 1; i < termos.size(); ++i) {
        if (r.empty()) {
            return {};
        }
        // pega a lista da nova palavra
        std::set<int> atual = index.getArchivesPerWords(termos[i]);
        // cria uma lista vazia para guardar o que for igual em ambas
        std::set<int> temp; 
        // aponta para o início da lista de resultados acumulados
        auto it1 = r.begin();
         // aponta para o início da lista da palavra atual
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

    //pega os ids do que ele esta procurando
    std::set<int> findIds = intersection(consulta);

    // se o id ta nessa lista, busca o nome do arquivo pelo id e insere no vetor de strings
    for (int id : findIds) {
        std::string nome = index.getNameArchivesPerId(id);
        nomesArquivos.push_back(nome);
    }
    
    return nomesArquivos;
}