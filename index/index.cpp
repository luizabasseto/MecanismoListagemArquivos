#include "index.hpp"

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

void Index::add(const std::string& palavra, const std::string& nomeArquivo) {
    int idDoc = getIdArchive(nomeArquivo);

    std::set<int>& ids = invertedIndex[palavra];

    ids.insert(idDoc);
}

std::set<int> Index::getArchivesPerWords(const std::string& palavra) const {
    auto it = invertedIndex.find(palavra);
    if (it != invertedIndex.end()) {
        return it->second; 
    }
    return std::set<int>();
}

std::string Index::getNameArchivesPerId(int id) const {
    auto it = mapIdToName.find(id);
    if (it != mapIdToName.end()) {
        return it->second;
    }
    return "Arquivo_não_conhecido";
}