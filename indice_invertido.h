#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class InvertedIndex {
public:
    void indice(const string& directory);
    
    vector<string> vetor_de_palavras(string frase);

    set<string> todas_presentes(vector<string> vetor_palavras);

private:
    map<string, map<string, int>> index;
};

#endif  // INVERTED_INDEX_H
