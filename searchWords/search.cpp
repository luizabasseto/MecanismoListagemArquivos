#include <iostream>
#include <vector>
#include <string>

using namespace std;

std::vector<string> binarySearch(vector<string> elem, vector<string> &vet, int n)
{
    int low = 0;
    long long comp = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (elem == vet[mid]){
            comp++;
            return {mid, comp};
        }
        if (elem > vet[mid]){
            comp++;
            low = mid + 1;
        }
        else{
            comp++;
            high = mid - 1;
        }
    }

    return {-1, comp};
}
