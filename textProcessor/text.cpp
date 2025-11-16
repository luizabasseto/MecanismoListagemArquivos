#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_set>
#include <cctype>

namespace fs = std::filesystem;

// Remove pontuação de uma palavra
std::string ClearWords(const std::string& palavra) {
    std::string limpa;
    for (char c : palavra) {
        if (std::isalpha((unsigned char)c)) {
            limpa += std::tolower(c);
        }
    }
    return limpa;
}

std::unordered_set<std::string> LoadingStopWords(const fs::path& path) {
    std::unordered_set<std::string> stopwords;
    std::ifstream file(path);

    if (!file) {
        std::cerr << "Erro ao abrir stopWords: " << path << "\n";
        return stopwords;
    }

    std::string palavra;
    while (file >> palavra) {
        stopwords.insert(palavra);
    }

    return stopwords;
}

std::vector<std::string> CreateNewArchiveClean(const std::string& directoryIn,
                                               const std::string& directoryOut)
{
    std::vector<std::string> arquivosGerados;
    fs::path dirPath(directoryIn);
    fs::path dirOut(directoryOut);

    auto stopwords = LoadingStopWords(dirPath / "stopwords.txt");

    if (!fs::exists(dirOut)) {
        fs::create_directory(dirOut);
    }

    for (const auto& entry : fs::directory_iterator(dirPath)) {

        if (entry.path().filename() == "stopwords.txt")
            continue;

        if (entry.is_regular_file() && entry.path().extension() == ".txt") {

            std::ifstream inFile(entry.path());
            if (!inFile) continue;

            fs::path newFile = dirOut / (entry.path().stem().string() + ".txt");

            std::ofstream outFile(newFile);

            std::string line;
            while (std::getline(inFile, line)) {

                std::stringstream ss(line);
                std::string palavra;

                while (ss >> palavra) {

                    std::string limpa = ClearWords(palavra);

                    if (limpa.empty()) continue;

                    if (stopwords.find(limpa) == stopwords.end()) {
                        outFile << limpa << " ";
                    }
                }

                outFile << "\n";
            }

            arquivosGerados.push_back(newFile.string());
            std::cout << "Gerado: " << newFile << "\n";
        }
    }

    return arquivosGerados;
}
