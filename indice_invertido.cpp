#include <iostream>
#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <map>
#include "normalizacao.h"
#include "indice_invertido.h"

using namespace std;

void InvertedIndex::indice(const string &directory)
{
    Normalizacao normalizacao;
    for (const auto &entry : __fs::filesystem::directory_iterator(directory))
    {
        try
        {
            ifstream infile(entry.path());
            if (infile.good())
            {
                string palavra;
                while (infile >> palavra)
                {
                    normalizacao.remover_caracter_especial(palavra);
                    if (!palavra.empty())
                    {
                        normalizacao.minusculo(palavra);
                        index[palavra][entry.path().filename()]++;
                    }
                }
                infile.close();
            }
            else{}
        }
        catch (...){}
    }
}
