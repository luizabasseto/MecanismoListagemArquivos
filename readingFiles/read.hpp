#ifndef ARCHIVES_HPP
#define ARCHIVES_HPP

#include <vector>
#include <string>		

using namespace std;

std::vector<int> ReadArchiveBin(string name, int n);

void createArchiveBin(string name, int n);

void createArchiveBinOrdenado(std::vector<int> vet, string name, int n);



#endif