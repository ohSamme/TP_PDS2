#include <string>
#include "normalizacao.h"

using namespace std;

void Normalizacao::minusculo(string& palavra)
{
    for (int i = 0; i < palavra.size(); i++)
    {
        if (palavra[i] >= 65 && palavra[i] <= 90)
        {
            palavra[i] = palavra[i] + 32;
        }
    }
}

void Normalizacao::remover_caracter_especial(string& palavra)
{
    string aux;
    for (int i = 0; i < palavra.size(); i++)
    {
        if ((palavra[i] >= 65 && palavra[i] <= 90) || (palavra[i] >= 97 && palavra[i] <= 122))
        {
            aux += palavra[i];
        }
    }
    palavra = aux;
}
