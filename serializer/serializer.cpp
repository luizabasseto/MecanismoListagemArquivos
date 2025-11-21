#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "serializer.hpp"

using namespace std;

void writeInteger(std::ofstream& out, int valor) {
    out.write(reinterpret_cast<const char*>(&valor), sizeof(valor));
}

int readInteger(std::ifstream& in) {
    int valor;
    in.read(reinterpret_cast<char*>(&valor), sizeof(valor));
    return valor;
}

void writeString(std::ofstream& out, const std::string& s) {
    int tamanho = s.size();
    writeInteger(out, tamanho);
    if (tamanho > 0) {
        out.write(s.data(), tamanho);
    }
}

std::string readString(std::ifstream& in) {
    int tamanho = readInteger(in);
    if (tamanho == 0) return "";
    
    std::string s;
    s.resize(tamanho);
    in.read(&s[0], tamanho);
    return s;
}


void Serializer::createArchiveBin(const Index& index, const std::string& caminhoArquivo) {
    std::ofstream out(caminhoArquivo, std::ios::binary);
    
    if (!out.is_open()) {
        std::cout << "Erro, não foi possivel criar o arquivo com o caminho " << caminhoArquivo << "\n";
        return;
    }

    writeInteger(out, index.nextId);

    int nArquivo = index.mapIdToName.size();
    writeInteger(out, nArquivo);

    for (const auto& par : index.mapIdToName) {
        writeInteger(out, par.first);
        writeString(out, par.second);
    }

    int nPalavras = index.invertedIndex.size();
    writeInteger(out, nPalavras);

    for (const auto& par : index.invertedIndex) {
        writeString(out, par.first);
        
        const std::set<int>& ids = par.second;
        writeInteger(out, ids.size());
        
        for (int id : ids) {
            writeInteger(out, id);
        }
    }

    out.close();
    std::cout << "Indice salvo com sucesso (" << nArquivo << " arquivos, " << nPalavras << " termos).\n";
}

Index Serializer::ReadArchiveBin(const std::string& caminhoArquivo) {
    Index index;
    std::ifstream in(caminhoArquivo, std::ios::binary);

    if (!in.is_open()) {
        std::cout << "Erro, arquivo de indice nao encontrado.\n";
        return index;
    }

    index.nextId = readInteger(in);
    int nArquivo = readInteger(in);

    for (int i = 0; i < nArquivo; ++i) {
        int id = readInteger(in);
        std::string nome = readString(in);
        
        index.mapIdToName[id] = nome;
        index.mapNameToId[nome] = id;
    }

    int nPalavras = readInteger(in);
    for (int i = 0; i < nPalavras; ++i) {
        std::string palavra = readString(in);
        int qtdIds = readInteger(in);
        
        std::set<int> ids;
        for (int j = 0; j < qtdIds; ++j) {
            int id = readInteger(in);
            ids.insert(id);
        }
        index.invertedIndex[palavra] = ids;
    }

    in.close();
    return index;
}