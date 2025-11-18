#include "text.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

TextProcessor::TextProcessor(const std::string& caminhoStopWords) {
    carregarStopWords(caminhoStopWords);
}

void TextProcessor::carregarStopWords(const std::string& caminhoArquivo) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Aviso: Nao foi possivel abrir o arquivo de stop words: " << caminhoArquivo << std::endl;
        return;
    }

    std::string palavra;
    while (arquivo >> palavra) {
        stopWords.insert(limparPalavra(palavra));
    }
    arquivo.close();
}

std::string TextProcessor::limparPalavra(const std::string& palavra) {
    std::string limpa;
    limpa.reserve(palavra.size());

    for (char c : palavra) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            limpa += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return limpa;
}

std::vector<std::string> TextProcessor::processar(const std::string& texto) {
    std::vector<std::string> tokens;
    std::stringstream ss(texto);
    std::string palavra;

    while (ss >> palavra) {
        std::string palavraLimpa = limparPalavra(palavra);

        if (palavraLimpa.empty()) continue;

        if (stopWords.find(palavraLimpa) == stopWords.end()) {
            tokens.push_back(palavraLimpa);
        }
    }

    return tokens;
}