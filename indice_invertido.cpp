#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <sstream>
#include <set>
#include "normalizacao.h"
#include "indice_invertido.h"

using namespace std;

void InvertedIndex::indice(const string& directory){
    Normalizacao normalizacao;
    for (const auto& entry : fs::filesystem::directory_iterator(directory)){
        try {
            ifstream infile(entry.path());
            if (infile.good()) {
                string palavra;
                while (infile >> palavra) {
                    normalizacao.remover_caracter_especial(palavra);
                    if (!palavra.empty()) {
                        normalizacao.minusculo(palavra);
                        index[palavra][entry.path().filename()]++;
                    }
                }
                infile.close();
            }
            else {
                throw runtime_error("Erro ao abrir o arquivo: " + entry.path().string());
            }
        }
        catch (...) {
            printf("Erro desconhecido!");
        }
    }
}