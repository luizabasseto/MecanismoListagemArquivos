#include <vector>
#include <string>
#include <unordered_set>

class TextProcessor {
private:
    std::unordered_set<std::string> stopWords;

    std::string clearWords(const std::string& palavra);

    void loadStopWords(const std::string& caminhoArquivo);

public:
    TextProcessor(const std::string& caminhoStopWords = "../library/stopwords.txt");

    std::vector<std::string> processedTexts(const std::string& texto);
};