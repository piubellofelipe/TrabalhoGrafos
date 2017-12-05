#include "No.h"
#include <iostream>
#include <limits>
#include <stdlib.h>
using namespace std;
No::No(int Id)
{
    this->id = Id;
    Adj = NULL;
    explorado = false;
    cor = 0;
    d=0;
}

No::~No()
{
    //dtor
}

void No::limpaListaAdj(){
    cout<<"deletando arestas..."<<endl;
    Aresta* aux;
    Aresta* a = getAresta();
    while (a != NULL){
        aux = a;
        a = aux->getProx();
        free(aux);
    }

    Adj = NULL;
    cout<<"arestas deletadas!"<<endl;

}

bool No::setAdj(Aresta* novo){
    Adj = novo;
}
bool No::addAresta(int Id, int w){
    Aresta* novo = new Aresta(Id);
    novo->setWeight(w);
    if (Adj == NULL)    Adj = novo;
    else{
        Aresta* aux = Adj;
        //cout<<Adj->getId();
        novo->setProx(aux);
        Adj = novo;
    }
    d++;
    return true;
}

bool No::delAresta(int Id){
    cout<<getId()<<endl;
    if (getGrau()==1 || getGrau()==0){d--;   setAdj(NULL); return true;}
    Aresta* anterior = NULL;
    Aresta* aux = getAresta();
    while (aux != NULL){
        if (aux->getId() == Id){ break;}
        if (aux->getProx() != NULL){ anterior = aux;  aux = aux->getProx();}
        else    break;
    }
    if (aux->getId() == Id){
        if (anterior != NULL){
            if (aux->getProx()!= NULL){ anterior->setProx(aux->getProx());}
            else    anterior->setProx(NULL);
            return true;
        }
        else if (aux->getProx()!=NULL){  setAdj(aux->getProx());}
        else{ setAdj(NULL);}
    }
    else{
        return false;
    }



}

bool No::addAresta(int Id){
    Aresta* novo = new Aresta(Id);
    if (Adj == NULL)    Adj = novo;
    else{
        Aresta* aux = Adj;
        novo->setProx(aux);
        Adj = novo;
    }
    d++;
    return true;
}

int No::getId(){
    //cout<<id<<endl;
    return id;
}

void No::imprimeAdj(){
    Aresta* aux = Adj;
    if (aux == NULL)    cout<<"Não há adjacentes de "<<getId()<<"!"<<endl;
    else    cout<<"\nLista de nós adjacentes de "<<getId()<<endl;
    while (aux != NULL){
        cout<<aux->getId()<<" ("<<aux->getWeight()<<"), ";
        aux = aux->getProx();
    }
    cout<<"\n"<<endl;
}
void No::imprimeGrau(){
    Aresta* aux = Adj;
    cout<<"\nGrau do nó "<<getId()<<" é: "<<d<<endl;
}

void No::setGrau(int d){
    int cont=0;
    Aresta* aux = Adj;
    while (aux != NULL){
        cont++;
        aux = aux->getProx();
    }
    d = cont;
}

bool No::verificaAdj(int Id){
    Aresta* aux = Adj;
    if (aux == NULL){   return false;}
    while (aux->getId()!=Id){
        if (aux->getProx() != NULL )aux = aux->getProx();
        else    break;
    }
    if(aux->getId() == Id){
        return true;
    }
    else
        return false;
}

int No::getPeso(int j){
    Aresta* aux = this->getAresta();
    if(aux==NULL) return std::numeric_limits<int>::max();
    else{
        while(aux!=NULL){
            int id=aux->getId();

            if(id==j) return aux->getWeight();

            aux = aux->getProx();
        }
    }
}
