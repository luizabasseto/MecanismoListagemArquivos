#include "Indexer.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

Index Indexer::build(const std::string& caminhoDiretorio) {
    Index indice;

    if (!fs::exists(caminhoDiretorio) || !fs::is_directory(caminhoDiretorio)) {
        std::cout << "Erro, o diretório " << caminhoDiretorio << " é invalido."<<std::endl;
        return indice;
    }

    fs::path caminhoAbsoluto = fs::absolute(caminhoDiretorio);
    indice.setDiretorioBase(caminhoAbsoluto.string());

    fs::path caminhoStop = fs::absolute("library/stopwords.txt");
    indice.setArquivoStopWords(caminhoStop.string());

    TextProcessor processador(caminhoStop.string());

    for (const auto& entry : fs::directory_iterator(caminhoDiretorio)) {
        
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            
            if (entry.path().filename() == "stopwords.txt") {
                continue;
            }
            
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