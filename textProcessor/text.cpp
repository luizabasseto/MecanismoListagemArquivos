#include "text.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

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
    //reserve a qauntidade de espaço necessário para a palavra
    limpa.reserve(palavra.size());

    for (char c : palavra) {
        //passa caractere por caractere da palavra, verifica se não é espaço e se não é pontuação
        if (!std::ispunct(static_cast<unsigned char>(c)) && 
            !std::isspace(static_cast<unsigned char>(c))) {
                //se não é, transforma o caractere para minusculo
            limpa += std::tolower(static_cast<unsigned char>(c));
        }
    }
    //retorna a palavra limpa
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