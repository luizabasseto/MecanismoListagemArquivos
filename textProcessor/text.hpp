#ifndef ARCHIVES_HPP
#define ARCHIVES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_set>

namespace fs = std::filesystem;

std::string ClearWords(const std::string& palavra);

std::unordered_set<std::string> loadingStopWords(const fs::path& path);

std::vector<std::string> CreateNewArchiveClean(const std::string &directoryIn, const std::string &directoryOut);

#endif