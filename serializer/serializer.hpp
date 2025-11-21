#include <vector>
#include <string>		
#include "index/index.hpp"

class Serializer{

    public:
        Serializer() = default;

        Index ReadArchiveBin(const std::string& caminhoArquivo);

        void createArchiveBin(const Index& index, const std::string& caminhoArquivo);

};