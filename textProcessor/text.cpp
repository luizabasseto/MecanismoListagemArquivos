#include "text.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <filesystem>
#include <utility>

namespace fs = std::filesystem;


std::string TextProcessor::converterAcentos(std::string palavra) {
    static const std::vector<std::pair<std::string, std::string>> substituicoes = {
        {"Á", "á"}, {"À", "à"}, {"Ã", "ã"}, {"Â", "â"},
        {"É", "é"}, {"Ê", "ê"},
        {"Í", "í"},
        {"Ó", "ó"}, {"Õ", "õ"}, {"Ô", "ô"},
        {"Ú", "ú"}, {"Ü", "ü"},
        {"Ç", "ç"},
    };

    for (const auto& par : substituicoes) {
        const std::string& maiuscula = par.first;
        const std::string& minuscula = par.second;

        size_t pos = 0;
        while ((pos = palavra.find(maiuscula, pos)) != std::string::npos) {
            palavra.replace(pos, maiuscula.length(), minuscula);
            pos += minuscula.length();
        }
    }
    return palavra;
}

TextProcessor::TextProcessor(const std::string& caminhoStopWords) {
    //pega o caminho absoluto do arquivo de StopWords
    fs::path caminho = fs::absolute(caminhoStopWords);
    loadStopWords(caminho.string());
}

void TextProcessor::loadStopWords(const std::string& caminhoArquivo) {
    //abre o arquivo das stop words
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        std::cout << "não foi possivel abrir o arquivo de stop words: " << caminhoArquivo << std::endl;
        return;
    }

    std::string palavra;
    //faz passar por cada palavra do arquivo
    while (arquivo >> palavra) {
        //a cada palavra, limpa ela (por garantia) e depois insere no unordered_set de stopWords
        stopWords.insert(clearWords(palavra));
    }
    arquivo.close();
}

std::string TextProcessor::clearWords(const std::string& palavra) {
    std::string limpa;
    limpa.reserve(palavra.size());

    for (char c : palavra) {
        unsigned char uc = static_cast<unsigned char>(c);

        if (uc == 0xE2 || uc == 0x80 || uc == 0x9C || uc == 0x9D) {
            continue; 
        }
        
        if (!std::ispunct(uc) && !std::isspace(uc)) {
            limpa += std::tolower(uc);
        }
    }

    limpa = converterAcentos(limpa);

    return limpa;
}

std::vector<std::string> TextProcessor::processedTexts(const std::string& texto) {
    std::vector<std::string> palavrasFinais;
    //transforma o texto em uma stringstream que quebra em "palavras" o texto inteiro 
    std::stringstream ss(texto);
    std::string palavra;

    while (ss >> palavra) {
        //para cada palavra do ss, pega ela e limpa para tirar pontuações e deixar em minusculo
        std::string palavraLimpa = clearWords(palavra);

        //se a palavra nao foi limpa por completo e nao sobrou nada
        if (palavraLimpa.empty()) continue;

        //se a palavra limpa nao é uma das stop words
        if (stopWords.find(palavraLimpa) == stopWords.end()) {
            //adiciona nas palavras finais
            palavrasFinais.push_back(palavraLimpa);
        }
    }
    //tokenização, retorna uma lista de palavras do texto.
    return palavrasFinais;
}