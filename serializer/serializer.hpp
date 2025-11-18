#include <vector>
#include <string>		
#include "index/index.hpp"

class Serializer{

    private:
        const Index& index;

    public:
        Serializer(const Index& idx);

        Index ReadArchiveBin(const std::string& caminhoArquivoBIN);

        void createArchiveBin(Index index, const std::string& caminhoArquivo);

};