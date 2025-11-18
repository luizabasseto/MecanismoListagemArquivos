#include <vector>
#include <string>
#include <set>
#include "index/index.hpp"

class QueryProcessor {
private:
    const Index& index;

    std::set<int> intersecao(const std::vector<std::string>& termos);

public:
    QueryProcessor(const Index& idx);

    std::vector<std::string> buscar(std::vector<std::string>& consulta);
};