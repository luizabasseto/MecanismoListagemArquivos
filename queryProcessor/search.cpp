#include "search.hpp"
#include <iostream>
#include <algorithm>

QueryProcessor::QueryProcessor(const Index& idx) : index(idx) {}

std::set<int> QueryProcessor::intersecao(const std::vector<std::string>& termos) {

    std::set<int> resultado = index.getArquivosPorPalavra(termos[0]);


    return resultado;
}

std::vector<std::string> QueryProcessor::buscar(std::vector<std::string>& consulta) {
    std::vector<std::string> nomesArquivos;

   
    return nomesArquivos;
}