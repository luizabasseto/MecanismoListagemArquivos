#include "index.hpp"

#include <iostream>

// pega qual é o id associado aquele arquivo
int Index::getIdArchive(const std::string& nomeArquivo) {
    if (mapNameToId.count(nomeArquivo)) {
        return mapNameToId[nomeArquivo];
    }

    int novoId = nextId;
    nextId++;

    mapNameToId[nomeArquivo] = novoId;
    mapIdToName[novoId] = nomeArquivo;

    return novoId;
}


// pega a palavra e associa a um id
void Index::add(const std::string& palavra, const std::string& nomeArquivo) {
    int idDoc = getIdArchive(nomeArquivo);

    std::set<int>& ids = invertedIndex[palavra];

    ids.insert(idDoc);
}

//pega os arquivos que aparece a palavra
std::set<int> Index::getArchivesPerWords(const std::string& palavra) const {
    auto it = invertedIndex.find(palavra);
    if (it != invertedIndex.end()) {
        return it->second; 
    }
    return std::set<int>();
}

// pega o nome dos arquivos que tem aquele Id
std::string Index::getNameArchivesPerId(int id) const {
    auto it = mapIdToName.find(id);
    if (it != mapIdToName.end()) {
        return it->second;
    }
    return "Arquivo_não_conhecido";
}



void Index::imprimirDebug() const {
    std::cout << "\n=== DEBUG: INDICE NA MEMORIA ===\n";
    
    for (const auto& par : invertedIndex) {
        std::cout << "[" << par.first << "] -> { ";
        for (int id : par.second) {
            std::cout << id << " ";
        }
        std::cout << "}\n";

    }
    std::cout << "================================\n";
}