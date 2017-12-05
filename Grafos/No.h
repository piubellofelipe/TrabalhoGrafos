#ifndef NO_H
#define NO_H
#include "Aresta.h"
#include <cstddef>
#include <iostream>

using namespace std;

class No
{
public:
    No(int Id);
    ~No();
    bool setAdj(Aresta* novo);
    bool addAresta(int Id);
    bool addAresta(int Id, int w);
    bool delAresta(int Id);
    int getId();
    void setId(int i){id=i;}
    int getGrau(){return d;}
    void imprimeGrau();
    void setGrau(int d);
    void imprimeAdj();
    bool verificaAdj(int Id);
    int getPeso(int j);
    Aresta* getAresta(){if (Adj != NULL) return Adj; else return NULL;}
    void limpaListaAdj();
    //int listGrau();
    //Getters e Setters
    bool explorado;
    int cor;
private:
    int id;//identificador do No
    Aresta *Adj = NULL;//lista de adjacência do No
    int d;//grau do No
    int w;//peso do No
};

#endif // NO_H