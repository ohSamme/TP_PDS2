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
            ifstream infile(entry.path());
            if (infile.good()) {
                string palavra;
                while (infile >> palavra) {
                    normalizacao.remover_caracter_especial(palavra);
                    if (!palavra.empty()) {
                        normalizacao.minusculo(palavra);
                        index[entry.path().filename()][palavra]++;
                    }
                }
                infile.close();
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
 
map<string, int> InvertedIndex::score(set<string> docs_relevantes, vector<string> vetor_palavras){

map<string,int> score;

for(auto pair:index){

    string documento = pair.first;

    map<string, int> ocorrencias = pair.second;

    if(docs_relevantes.count(documento) > 0){

        int score_documento = 0;

        for(auto palavra : vetor_palavras){
            if(ocorrencias.count(palavra) > 0 ){

            score_documento += ocorrencias[palavra];

            }
        }

        score[documento] = score_documento;
    }
}

return score;
}

void InvertedIndex::imprimir_documentos(string consulta){

    vector<string> palavras = vetor_de_palavras(consulta);
    set<string> documentosRelevantes = todas_presentes(palavras);
    map<string, int> documentosScore = score(documentosRelevantes, palavras);
    vector<pair<string, int>> documentosOrdenados(documentosScore.begin(), documentosScore.end());

    sort(documentosOrdenados.begin(), documentosOrdenados.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second)
            return a.second > b.second;
        return a.first < b.first;
    });

    for (auto documento : documentosOrdenados) {
        cout << documento.first << endl;
    }
}
