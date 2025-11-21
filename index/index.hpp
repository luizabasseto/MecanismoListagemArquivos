#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <set>

class Index {
private:
    std::unordered_map<std::string, std::set<int>> invertedIndex;
    std::unordered_map<std::string, int> mapNameToId;
    std::unordered_map<int, std::string> mapIdToName;

    int nextId = 0;

    int getIdArchive(const std::string& nomeArquivo);

public:

    void add(const std::string& palavra, const std::string& nomeArquivo);

    std::set<int> getArchivesPerWords(const std::string& palavra) const;

    std::string getNameArchivesPerId(int id) const;

    int getLastId() const { return nextId; }
    void setLastId(int id) { nextId = id; }

    friend class Serializer;
};