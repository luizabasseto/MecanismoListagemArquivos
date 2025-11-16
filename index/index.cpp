#include "index.hpp"

int Index::getIdArquivo(const std::string& nomeArquivo) {
    if (mapaNomeParaId.count(nomeArquivo)) {
        return mapaNomeParaId[nomeArquivo];
    }

    int novoId = proximoId;
    proximoId++;

    mapaNomeParaId[nomeArquivo] = novoId;
    mapaIdParaNome[novoId] = nomeArquivo;

    return novoId;
}

void Index::adicionar(const std::string& palavra, const std::string& nomeArquivo) {
    int idDoc = getIdArquivo(nomeArquivo);

    std::set<int>& ids = indiceInvertido[palavra];

    ids.insert(idDoc);
}

std::set<int> Index::getArquivosPorPalavra(const std::string& palavra) const {
    auto it = indiceInvertido.find(palavra);
    if (it != indiceInvertido.end()) {
        return it->second; 
    }
    return std::set<int>();
}

std::string Index::getNomeArquivoPorId(int id) const {
    auto it = mapaIdParaNome.find(id);
    if (it != mapaIdParaNome.end()) {
        return it->second;
    }
    return "ARQUIVO_DESCONHECIDO";
}