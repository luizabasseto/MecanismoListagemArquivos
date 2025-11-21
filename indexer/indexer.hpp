#include <string>
#include "../index/index.hpp" 
#include "../textProcessor/text.hpp"

class Indexer {
public:
    Index build(const std::string& caminhoDiretorio);
};
