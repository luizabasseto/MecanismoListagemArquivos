#include <iostream>
#include <vector>
#include <string>

#include "searchWords/search.hpp"

int main() {

    int option=0;
    std::cout << "Bem vindo ao mecanismo de busca para documentos de texto!! \n";
    while (option != 1 && option != 2) {
        std::cout << "Digite sua opção de escolha \n";
        std::cout << "(1) - Digite 1 para Indexar um arquivo \n";
        std::cout << "(2) - Digite 2 caso queira buscar uma palavra \n";
        std::cin >> option;

        if(option!=1&&option!=2){
            std::cout <<"Opção errada! \n";
        }
    }

    std::vector<std::string> wordsLists;
    std::vector<std::string> docLists;
    int stop=1;
    switch (option)
    {
    case 1:
        break;
    
    case 2:
        while (stop!=0)
        {
            std::cout << "Para sair da busca, digite 0. \n";
            std::cout << "Digite a(s) palvra(s) que deseja encontrar: \n";
            std::string input;
            std::cin >> input;
            if (input == "0") {
                stop = 0;
            } else {
                wordsLists.push_back(input);
            }
        }

        if(wordsLists.size()==1){
            docLists = findOneWord(wordsLists);
        } else{
            docLists = findListWords(wordsLists);
        }
        
        break;
    default:
        break;
    }


    return 0;
}
