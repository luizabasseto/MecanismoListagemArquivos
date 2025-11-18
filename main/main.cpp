#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "queryProcessor/search.hpp"

int main(int argc, char* argv[]) {
    QueryProcessor searches;

    if (argc < 2) {
        std::cerr << "Erro: Nenhum comando fornecido." << std::endl;
        std::cerr << "Uso: indice <construir|buscar> [argumentos]" << std::endl;
        return 1;
    }

    std::string comando = argv[1];

    if (comando == "construir") {
        if (argc != 3) {
            std::cerr << "Uso: indice construir <caminho_do_diretorio>" << std::endl;
            return 1;
        }
        std::string diretorio = argv[2];
        
        std::cout << "Iniciando indexação do diretório: " << diretorio << std::endl;
        
        
        std::cout << "Indexação concluída." << std::endl;

    } else if (comando == "buscar") {
        if (argc < 3) {
            std::cerr << "Uso: indice buscar <termo1> [termo2] ... [termoN]" << std::endl;
            return 1;
        }

        std::vector<std::string> wordsLists;
        for (int i = 2; i < argc; ++i) {
            wordsLists.push_back(argv[i]);
        }

        std::set<std::string>  = searches.buscar(wordsLists);
        

    } else {
        std::cerr << "Comando desconhecido: " << comando << std::endl;
        return 1;
    }

    return 0;
}