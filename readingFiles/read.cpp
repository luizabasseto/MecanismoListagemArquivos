#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::vector<std::string> CreateListDirectory(const std::string& directory)
{
    std::vector<std::string> result;
    fs::path dirPath(directory);

    if (!fs::exists(dirPath)) {
        std::cout << "Caminho inválido.\n";
        return result;
    }

    for (const auto& entry : fs::directory_iterator(dirPath)) {
        result.push_back(entry.path().string());
        std::cout << entry.path() << '\n';
    }

    return result;
}

std::vector<std::string> CreateNewArchiveClean(const std::string& directory)
{
    fs::path dirPath(directory);
    
    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::ifstream inFile(entry.path());
            if (!inFile) continue;

            // cria novo nome: exemplo.txt → exemplo_out.txt
            fs::path newFile = entry.path().stem().string() + "_out.txt";
            std::ofstream outFile(newFile);

            std::string line;
            while (std::getline(inFile, line)) {
                // transforma o texto em maiúsculas (exemplo de "processamento")
                for (char& c : line) c = std::toupper(c);
                outFile << line << "\n";
            }

            std::cout << "Gerado: " << newFile << "\n";
        }
    }
}