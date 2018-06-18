#include "Aresta.h"
#include <iostream>
using namespace std;
Aresta::Aresta(int Id)
{
    id = Id;
    w = 0;
    prox = NULL;
    cor = 0;
}

Aresta::~Aresta()
{
    //dtor
}



bool Aresta::setProx(Aresta* p){
    prox = p;
    return true;
}

Aresta* Aresta::getProx(){
    if(prox!= NULL) return prox;
    else	return NULL;
}