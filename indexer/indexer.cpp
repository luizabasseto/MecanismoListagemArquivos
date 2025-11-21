#include "Indexer.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

Index Indexer::build(const std::string& caminhoDiretorio) {
    Index indice;
    TextProcessor processador;

    if (!fs::exists(caminhoDiretorio) || !fs::is_directory(caminhoDiretorio)) {
        std::cout << "Erro, o diretório " << caminhoDiretorio << " é invalido."<<std::endl;
        return indice;
    }

    for (const auto& entry : fs::directory_iterator(caminhoDiretorio)) {
        
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            
            std::string caminhoArquivo = entry.path().string();
            std::ifstream arquivo(caminhoArquivo);
            
            if (arquivo.is_open()) {
                std::stringstream buffer;
                buffer << arquivo.rdbuf();
                std::string conteudo = buffer.str();
                
                std::vector<std::string> palavras = processador.processedTexts(conteudo);

                for (const std::string& palavra : palavras) {
                    indice.add(palavra, entry.path().filename().string());
                }
                
                arquivo.close();
                std::cout << "Arquivo indexado: " << entry.path().filename() << std::endl;
            }
        }
    }

    return indice;
}