#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "index/index.hpp"
#include "serializer/Serializer.hpp"
#include "queryProcessor/search.hpp" 
#include "indexer/indexer.hpp"
#include "textProcessor/text.hpp"

const std::string arquivoTextos = "index.dat";

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        std::cout << "Nenhum comando foi fornecido." << std::endl;
        return 1;
    }

    std::string comando = argv[1];

    if (comando == "construir") {
       if (argc != 3) {
            std::cout << "Erro, forma de comando errada." << std::endl;
            std::cout << "Faça do seguinte modo: ./indice construir <caminho_do_diretorio>" << std::endl;
            return 1;
        }
        std::string diretorio = argv[2];
        if (!std::filesystem::exists(diretorio) || !std::filesystem::is_directory(diretorio)) {
            std::cout << "Erro, o diretorio '" << diretorio << "' não existe ou é inválido." << std::endl;
            return 1; 
        }
        
        std::cout << "Iniciando indexação do diretório: " << diretorio << std::endl;
        
        Indexer indexer;
        Index indices = indexer.build(diretorio);
        
        Serializer serializer;
        serializer.createArchiveBin(indices, arquivoTextos);
        
        std::cout << "Indexação concluída. Índice salvo em " << arquivoTextos << std::endl;

    } else if (comando == "buscar") {
        if (argc < 3) {
            std::cout << "Erro, forma de comando errada." << std::endl;
            std::cout << "Faça do seguinte modo: indice buscar <termo1> [termo2] ... [termoN]" << std::endl;
            return 1;
        }

        if (!std::filesystem::exists(arquivoTextos)) {
            std::cout << "Erro, arquivo '" << arquivoTextos << "' não encontrado." << std::endl;
            std::cout << "Execute o comando 'construir' primeiro." << std::endl;
            return 1;
        }

        Serializer serializer;
        Index indices = serializer.ReadArchiveBin(arquivoTextos);

        QueryProcessor search(indices);
        std::string caminhoStopWords = indices.getArquivoStopWords();
    
        TextProcessor text(caminhoStopWords);

        std::vector<std::string> termosBusca;
        
        for (int i = 2; i < argc; ++i) {
            std::string termo = argv[i];
            std::vector<std::string> termosLimpo = text.processedTexts(termo);
            
            for (const auto& termo : termosLimpo) {
                termosBusca.push_back(termo);
            }
        }

        std::vector<std::string> resultados = search.searches(termosBusca);
        
        if (resultados.empty()) {
            std::cout << "Nenhum documento encontrado para os termos fornecidos." << std::endl;
        } else {
            std::cout << "Documentos encontrados (" << resultados.size() << "):" << std::endl;
            for (const auto& doc : resultados) {
                std::cout << doc << std::endl;
            }
        }

    } else {
        std::cout << "Comando desconhecido: " << comando << std::endl;
        return 1;
    }

    return 0;
}