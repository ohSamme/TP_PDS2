#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class InvertedIndex {
public:
    void indice(const string& directory);
    vector<string> search(const string& frase) const;

private:
    map<string, map<string, int>> index;
};

#endif  // INVERTED_INDEX_H
