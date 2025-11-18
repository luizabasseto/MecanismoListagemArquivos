#include <vector>
#include <string>
#include <unordered_set>

class TextProcessor {
private:
    std::unordered_set<std::string> stopWords;

    std::string limparPalavra(const std::string& palavra);

    void carregarStopWords(const std::string& caminhoArquivo);

public:
    TextProcessor(const std::string& caminhoStopWords = "library/stopwords.txt");

    std::vector<std::string> processar(const std::string& texto);
};