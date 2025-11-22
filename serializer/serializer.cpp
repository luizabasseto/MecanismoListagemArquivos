#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "serializer.hpp"

using namespace std;

//le um numero int e retorna ele em um ponteiro de char(bytes) transformando para binário
void writeInteger(std::ofstream& out, int valor) {
    out.write(reinterpret_cast<const char*>(&valor), sizeof(valor));
}

//le um numero em bytes (binario) e retorna o valor em int
int readInteger(std::ifstream& in) {
    int valor;
    in.read(reinterpret_cast<char*>(&valor), sizeof(valor));
    return valor;
}

//escreve a string em binario
void writeString(std::ofstream& out, const std::string& s) {
    int tamanho = s.size();
    writeInteger(out, tamanho);
    if (tamanho > 0) {
        out.write(s.data(), tamanho);
    }
}

//le a string em binario
std::string readString(std::ifstream& in) {
    int tamanho = readInteger(in);
    if (tamanho == 0) return "";
    
    std::string s;
    s.resize(tamanho);
    in.read(&s[0], tamanho);
    return s;
}


//serialize o Index e transforma em binario
void Serializer::createArchiveBin(const Index& index, const std::string& caminhoArquivo) {
    std::ofstream out(caminhoArquivo, std::ios::binary);
    
    if (!out.is_open()) {
        std::cout << "Erro, não foi possivel criar o arquivo com o caminho " << caminhoArquivo << "\n";
        return;
    }

    //guarda o caminho do arquivo das stopWords e onde estão os arquivos base ( no caso library)
    writeString(out, index.diretorioBase); 
    writeString(out, index.arquivoStopWords); 

    writeInteger(out, index.nextId);

    //escreve primeiro a quantidade de arquivos gerais
    int nArquivo = index.mapIdToName.size();
    writeInteger(out, nArquivo);

    //escreve par por par de ids e nomes dos arquivos
    for (const auto& par : index.mapIdToName) {
        writeInteger(out, par.first);
        writeString(out, par.second);
    }

    //escreve a quantidade de palavras existentes em todos os arquivos
    int nPalavras = index.invertedIndex.size();
    writeInteger(out, nPalavras);

    //escreve deopois par por par do index invertido (ids e palavras)
    for (const auto& par : index.invertedIndex) {
        //escreve a palavra
        writeString(out, par.first);
        
        const std::set<int>& ids = par.second;
        //escreve em quantos documentos a palavra esta
        writeInteger(out, ids.size());
        
        //escreve os ids dos documentos onde a palavra esta
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

    //lê os diretorios da stopWords e do diretorio dos arquivos
    index.diretorioBase = readString(in);
    index.arquivoStopWords = readString(in); 

    index.nextId = readInteger(in);
    int nArquivo = readInteger(in);

    //le os ids e nome dos arquivos
    for (int i = 0; i < nArquivo; ++i) {
        int id = readInteger(in);
        std::string nome = readString(in);
        
        index.mapIdToName[id] = nome;
        index.mapNameToId[nome] = id;
    }

    //lê as palavras
    int nPalavras = readInteger(in);
    for (int i = 0; i < nPalavras; ++i) {
        std::string palavra = readString(in);
        //lê em quantos ids (documentos) a palavra aparece
        int qtdIds = readInteger(in);
        
        std::set<int> ids;
        for (int j = 0; j < qtdIds; ++j) {
            //lê os id e insere no set
            int id = readInteger(in);
            ids.insert(id);
        }
        //associa cada palavra ao id dela
        index.invertedIndex[palavra] = ids;
    }

    in.close();
    return index;
}