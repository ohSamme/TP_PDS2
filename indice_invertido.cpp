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
    for (const auto& entry : filesystem::directory_iterator(directory)){
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

vector<string> InvertedIndex::vetor_de_palavras(string frase){

    stringstream ss(frase);
    string palavra;
    vector<string> vetor_palavras;

    while(ss >> palavra){
        Normalizacao normalizacao;
        normalizacao.remover_caracter_especial(palavra);
        normalizacao.minusculo(palavra);
        
        if(!palavra.empty()){
            vetor_palavras.push_back(palavra);
        }
    }
    return vetor_palavras;
}

set<string> InvertedIndex::todas_presentes(vector<string> vetor_palavras){

    set<string> documentosRelevantes;

    for(auto pair : index){
        string documento = pair.first;
        map<string, int> ocorrencias = pair.second;

        bool todas_palavras = true;

        for(string palavraConsulta : vetor_palavras){
            if(ocorrencias.count(palavraConsulta) == 0){
                todas_palavras = false;
                break;
                }
            }
        if(todas_palavras == true){
            documentosRelevantes.insert(documento);
        }
    }
    
    return documentosRelevantes;  
 }