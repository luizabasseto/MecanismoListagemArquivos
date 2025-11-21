#include "text.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

TextProcessor::TextProcessor(const std::string& caminhoStopWords) {
    fs::path caminho = fs::absolute(caminhoStopWords);
    loadStopWords(caminho.string());
}

void TextProcessor::loadStopWords(const std::string& caminhoArquivo) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        std::cout << "não foi possivel abrir o arquivo de stop words: " << caminhoArquivo << std::endl;
        return;
    }

    std::string palavra;
    while (arquivo >> palavra) {
        stopWords.insert(clearWords(palavra));
    }
    arquivo.close();
}

std::string TextProcessor::clearWords(const std::string& palavra) {
    std::string limpa;
    limpa.reserve(palavra.size());

    for (char c : palavra) {
        if (!std::ispunct(static_cast<unsigned char>(c)) && 
            !std::isspace(static_cast<unsigned char>(c))) {
            limpa += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return limpa;
}

std::vector<std::string> TextProcessor::processedTexts(const std::string& texto) {
    std::vector<std::string> palavrasFinais;
    std::stringstream ss(texto);
    std::string palavra;

    while (ss >> palavra) {
        std::string palavraLimpa = clearWords(palavra);

        if (palavraLimpa.empty()) continue;

        if (stopWords.find(palavraLimpa) == stopWords.end()) {
            palavrasFinais.push_back(palavraLimpa);
        }
    }

    return palavrasFinais;
}