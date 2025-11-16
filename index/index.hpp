#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <set>

class Index {
private:
    std::unordered_map<std::string, std::set<int>> indiceInvertido;

    std::unordered_map<std::string, int> mapaNomeParaId;
    std::unordered_map<int, std::string> mapaIdParaNome;

    int proximoId = 0;

    int getIdArquivo(const std::string& nomeArquivo);

public:

    void adicionar(const std::string& palavra, const std::string& nomeArquivo);

    std::set<int> getArquivosPorPalavra(const std::string& palavra) const;

    std::string getNomeArquivoPorId(int id) const;

};