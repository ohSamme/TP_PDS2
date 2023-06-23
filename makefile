tp_execution: indice_invertido.o main.o normalizacao.o
	g++ *.o -o tp_execution

indice_invertido.o: normalizacao.o indice_invertido.h
	g++ -c indice_invertido.cpp -o indice_invertido.o

normalizacao.o: normalizacao.h 
	g++ -c normalizacao.cpp -o normalizacao.o

main.o: main.cpp indice_invertido.o normalizacao.o
	g++ -c main.cpp -o main.o

limpar:
	rm -f tp_execution *.o