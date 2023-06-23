#include <iostream>
#include <string>
#include "indice_invertido.h"

int main()
{
    InvertedIndex invertedIndex;
    
    invertedIndex.indice("./documentos");

    std::cout << "Insira uma frase para pesquisa: ";

    std::string consulta;

    std::getline(std::cin, consulta);

    invertedIndex.imprimir_documentos(consulta);

    return 0;
}
