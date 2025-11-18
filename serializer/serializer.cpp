#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "serializer.hpp"

using namespace std;

void createArchiveBin(Index index, const std::string& name)
{
    std::string filename = "../../binaryArchives/" + name + ".dat";

    std::ofstream archive(filename, std::ios::binary);
    if (!archive)
    {
        std::cerr << "Erro ao abrir arquivo Index para escrita.\n";
        return;
    }

    for (int num : index.getNomeArquivoPorId())
    {
        uint32_t val = static_cast<uint32_t>(num);
        archive.write(reinterpret_cast<const char *>(&val), sizeof(val));
    }

    archive.close();
}


Index ReadArchiveBin(const std::string& name)
{
    std::string filename = "../../binaryArchives/" + name + ".dat";
    Index vet;

    std::ifstream archive(filename, std::ios::binary);
    if (!archive)
    {
        std::cerr << "Erro ao abrir arquivo binário para leitura.\n";
        return vet;
    }

    for (int i = 0; i < n; i++)
    {
        uint32_t val;
        archive.read(reinterpret_cast<char *>(&val), sizeof(val));
        if (archive.gcount() == sizeof(val))
        {
            vet.push_back(static_cast<int>(val));
        }
        else
        {
            break;
        }
    }

    archive.close();
    return vet;
};