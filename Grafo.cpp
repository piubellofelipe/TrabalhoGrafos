#include "Grafo.h"
#include <iostream>
#include <stdlib.h>
#include <limits>


using namespace std;

Grafo::Grafo(bool temPeso, string arquivo)
{
    n=0;
    nNos=0;
    m=0;
    D=0;

    readFile(arquivo, temPeso);

}

Grafo::Grafo(int Id, int tam){
    nNos = 0;
    m=0;
    D=0;
    n = tam;
    listaNo = (No **)malloc(tam*sizeof(No));
    for (int i=0; i<tam; i++){
        listaNo[i] = NULL;
    }
    //cout<<Id<<" ";
    addNo(Id);
}

Grafo::Grafo(int tam){
    nNos = 0;
    m=0;
    D=0;
    n = tam;
    listaNo = (No**)malloc(tam*sizeof(No));
    for (int i=0; i<tam; i++){
        listaNo[i] = NULL;
    }
}

Grafo::~Grafo()
{
    /*
    for (int i=0; i<n; i++){
          cout<<"deletando nós..."<<endl;
         cout<<i<<endl;
    cout<<nNos<<endl;
    if (listaNo[i] != NULL){
        cout<<"a"<<endl;
    listaNo[i]->limpaListaAdj();
    delete listaNo[i];
       }
    }

    delete ArvMin;
*/
}

int Grafo::Hash(int Id){ //DETERMINA UM VALOR HASH PARA UMA ENTRADA
    return Id%n;
}

bool Grafo::procuraNo(int Id){
    return listaNo[Hash(Id)] != NULL && listaNo[Hash(Id)]->getId() == Id;
}

bool Grafo::addNo(int Id){ //ADICIONA UM OBJETO DO TIPO NO NA LISTA DE NÓS DO GRAFO

    if (procuraNo(Id))   return false;//nó já adicionado

    if (Id<0)   return false;

    listaNo[Hash(Id)] = new No(Id);

    nNos +=1;

    if (nNos == 1)  primeiro = listaNo[Hash(Id)];
    return true;
}

bool Grafo::delNo(int Id){
    if (!procuraNo(Id))   return false;
    Aresta* prox = listaNo[Hash(Id)]->getAresta();
    if (listaNo[Hash(Id)]->getGrau() == 0)       listaNo[Hash(Id)] == NULL;

    while(prox != NULL){
        int proximo = prox->getId();
        listaNo[Hash(proximo)]->delAresta(2);
        if (prox->getProx()!= NULL) prox = prox->getProx();
        else    break;
    }

    listaNo[Hash(Id)] = NULL;

}
bool Grafo::addAresta(int Id1, int Id2, int w){
    addNo(Id1); addNo(Id2);
    listaNo[Hash(Id1)]->addAresta(Id2,w);
    listaNo[Hash(Id2)]->addAresta(Id1, w);
    m++;
    if (D<listaNo[Hash(Id1)]->getGrau())    D = listaNo[Hash(Id1)]->getGrau();
    if (D<listaNo[Hash(Id2)]->getGrau())    D = listaNo[Hash(Id2)]->getGrau();
}

bool Grafo::addAresta(int Id1, int Id2){
    if (ehAdj(Id1, Id2))    return 0;
    addNo(Id1); addNo(Id2);
    listaNo[Hash(Id1)]->addAresta(Id2);
    listaNo[Hash(Id2)]->addAresta(Id1);
    m++;
    if (D<listaNo[Hash(Id1)]->getGrau())    D = listaNo[Hash(Id1)]->getGrau();
    if (D<listaNo[Hash(Id2)]->getGrau())    D = listaNo[Hash(Id2)]->getGrau();
}

void Grafo::imprimeNo(){
    int Id=0;
    while(Id<n){
        if (listaNo[Hash(Id)] != NULL){
            listaNo[Hash(Id)]->imprimeAdj();

        }
        Id++;
    }
}

void Grafo::imprimeCorNo(){
    int Id=0;
    while(Id<n){
        if (listaNo[Hash(Id)] != NULL){
            cout<<"Id :"<<Id<<" cor:"<<listaNo[Hash(Id)]->cor<<endl;
            Aresta *aux = listaNo[Hash(Id)]->getAresta();
            cout<<"adjacentes: \n";
            while (aux != NULL){
                cout<<"id "<<aux->getId()<<" cor: da aresta: "<<aux->cor<<endl;
                aux = aux->getProx();
                cout<<"----------------------\n";
            }
        }
        Id++;
    }
}

void Grafo::imprimeGrauNo(){
    int Id=0;
    while(Id<n){
        if (listaNo[Hash(Id)] != NULL)  listaNo[Hash(Id)]->imprimeGrau();
        Id++;
    }
}

void Grafo::setGrauGrafo(int Id){
    int aux=0;
    int maior=0;
    int j=0;
    while(listaNo[Hash(Id)] != NULL){
        aux=listaNo[Hash(Id)]->getGrau();
        if(aux>maior){
            maior=aux;
        }
    }

    D=maior;
}

void Grafo::kRegular(){
    int Id=0, i=0; int aux=0;
    while (listaNo[Id] == NULL) Id++;
    if(listaNo[Id]!=NULL)  aux = listaNo[Id]->getGrau();
    while(Id<n){
        if (listaNo[Id]!=NULL && listaNo[Id]->getGrau() != aux){
            i=1;    break;
        }
        else Id++;
    }
    if (i==1)   cout<<"O grafo não é k-regular!"<<endl;
    else        cout<<"O grafo é k-regular!"<<endl;
}

void Grafo::seqGrauGrafo(){


    int j=0, vet[n], i=0;
    while (j<n){
        if (listaNo[j] != NULL){
            vet[i]=listaNo[j]->getGrau();
            //cout<<vet[i]<<" ";
            i++;
        }
        j++;
    }
    cout<<endl;
    ShellSort(vet);
//    cout<<"Sequência de graus: < ";
    for(int i=0; i<n; i++){
        cout<<vet[i]<<" ";
    }
    cout<<">"<<endl;



}

void Grafo::completo(){
    int Id=0, i=0;
    while(Id<n){
        if(listaNo[Id] != NULL && D!=listaNo[Id]->getGrau()){
            cout<<"O grafo nao é completo"<<endl;
            i=1;
            break;
        }
        Id++;
    }
    if(i==0)
        cout<<"O grafo é completo"<<endl;
}

bool Grafo::ehAdj(int Id1, int Id2){
    if (!procuraNo(Id1))    return false;
    return    listaNo[Hash(Id1)]->verificaAdj(Id2);
}

bool Grafo::readFile(string txt, bool temPeso){
    std::ifstream file(txt.c_str());
    std::string str;
    int i=0;
    char x;
    int y=0, tam, w=0;
    file>>tam;
    n = tam+1;
    listaNo = (No **)malloc(tam*sizeof(No));

    if (!temPeso){
        //cout<<"sem peso"<<endl;
        for (int i=0; i<n; i++){
            listaNo[i] = NULL;
        }
        while (file>>y && file>>w){// && file>>w) {

            addAresta(y, w);
            //cout<<y<<" "<<w<<endl;
        }
    }
    else{
        for (int i=0; i<n; i++){
            listaNo[i] = NULL;
        }
        while (file>>x && file>>y && file>>w){
            addAresta(x,y,w);
            //cout<<x<<" "<<y<<" "<<w<<endl;
        }
    }

    return true;
}
bool Grafo::buscaProfundidade(int Id,int pai, int nivel, int buscando){
    if (!procuraNo(Id)) return false;

    //if (nivel != 0) cout<<"No: "<<Id<<" Pai: "<< pai <<" Nivel: "<<nivel<<"\n";

    listaNo[Hash(Id)]->explorado = true;

    Aresta* a = listaNo[Hash(Id)]->getAresta();
    while (a != NULL){
        int Id2 = a->getId();

        if (!(listaNo[Hash(Id2)]->explorado)){
            buscaProfundidade(a->getId(),Id, nivel+1);
        }
        a = a->getProx();
    }
    return false;

}

void Grafo::buscaProfundidade(int Id,int pai, int nivel){
    if (!procuraNo(Id)) return;
    listaNo[Hash(Id)]->explorado = true;

    Aresta* a = listaNo[Hash(Id)]->getAresta();
    while (a != NULL){
        int Id2 = a->getId();
        if (!(listaNo[Hash(Id2)]->explorado)){
            buscaProfundidade(a->getId(),Id, nivel+1);
        }
        a = a->getProx();
    }

}
bool Grafo::buscaLargura(int Id,int Id2){
    desmarcar();
    int fila[n], k=0;
    if (listaNo[Hash(Id)] == NULL){
        cout<<"Não encontrou "<<Id<<" no Grafo."<<endl;
        return false;
    }
    if (listaNo[Hash(Id2)] == NULL){
        cout<<"Não encontrou "<<Id2<<" no Grafo."<<endl;
        return false;
    }
    listaNo[Hash(Id)]->explorado = true;
    fila[0]= Id;
    k++;

    for (int i=0;
         i<k; i++){
        if (listaNo[Hash(fila[i])] == NULL) continue;
        No* node = listaNo[Hash(fila[i])];
        if (fila[i] == Id2) return true;
        Aresta* aux = node->getAresta();
        while (aux != NULL){
            int id = aux->getId();
            if (!listaNo[Hash(id)]->explorado){
                fila[k] = id;
                listaNo[Hash(id)]->explorado = true;
                k++;
            }
            aux = aux->getProx();

        }

    }

    //free(fila);
    return false;
}

bool Grafo::naoEstaContido(Aresta2 A2, Aresta2 S[]){
    int id1 = A2.id1;
    int id2 = A2.id2;

    for (int j=0; j<m; j++){
        if ( (S[j].id1 == id2 && S[j].id2 == id1 ) || (S[j].id1 == id1 && S[j].id2 == id2)  )
            return false;
    }
    return true;
}


void Grafo::ShellSort(int num[]){//ordena um vetor de inteiros
    int i, flag=1, numLength = nNos;
    int d = numLength;
    int temp;
    while (flag || (d>1)){
        flag = 0;
        d = (d+1)/2;
        for (i=0; i<(numLength - d); i++){
            if (num[i+d] > num[i]){
                temp = num[i+d];
                num[i+d] = num[i];
                num[i] = temp;
                flag = 1;
            }
        }

    }
    return;
}

void Grafo::ShellSortArestas(Aresta2 num[]){//ordena um vetor de nós pelo grau
    int i, flag=1, numLength = nNos;
    int d = numLength;
    Aresta2 temp;
    while (flag || (d>1)){
        flag = 0;
        d = (d+1)/2;
        for (i=0; i<(numLength - d); i++){
            if (num[i+d].w > num[i].w){
                temp = num[i+d];
                num[i+d] = num[i];
                num[i] = temp;
                flag = 1;
            }
        }

    }
    return;
}



Grafo Grafo::SomaArvores(int G[], Aresta2 S[]){
    ShellSortArestas(S);

    ArvMin = new Grafo(getN());
    for (int i=0; i<n; i++){
        ArvMin->addNo(G[i]);
    }
    for (int j=0; j<m;j++){
        int id1 = S[j].id1;
        int id2 = S[j].id2;
        int w = S[j].w;
        //cout<<"buscando caminho de "<<id1<<" a "<<id2<<endl;
        if (!ArvMin->buscaLargura(id1, id2)){
            //ArvMin->imprimeNo();
          //  cout<<"Não achou caminho de "<<id1<<" a "<<id2<<endl;
            ArvMin->addAresta(id1, id2, w);
        }
        else{
            //cout<<"achou caminho de "<<id1<<" a "<<id2<<endl;
        }
    }
    ArvMin->imprimeNo();
}


Grafo Grafo::ArvoreGerMinKruskel(){
    int vet[n];
    cout<<"ene: "<<n<<endl;
    //cout<<m<<endl;
    struct Aresta2 S[m];

    int j=0;
    int i=0;
    int k=0;

    for (j=0; j<n; j++){
        if (listaNo[j] != NULL){
            vet[i] = (listaNo[j]->getId());
            i++;
            Aresta* a = listaNo[j]->getAresta();
            while (a != NULL){
                Aresta2 a2;
                a2.id1 = listaNo[j]->getId();
                a2.id2 = a->getId();
                a2.w = a->getWeight();
                if ( naoEstaContido(a2, S) ){
                    S[k] = a2;
                    k++;
                }
                a = a->getProx();
            }
        }
    }


    SomaArvores(vet, S);


}
void Grafo::Floyd(){

    int tam = nNos;
    cout<<tam<<endl;
    //tam = 10000;

    //cout<<n<<endl;
    //int matriz[tam+1][tam+1];
    int **matriz;
    matriz = (int **)malloc(tam * sizeof(int *));
    for (int i=0; i<tam; i++){
        matriz[i] = (int *)malloc(tam*sizeof(int));

    }

    for(int i=1;i<tam;i++){
        for(int j=1;j<tam;j++){
            matriz[i][j] = 999999999;

        }
    }


    for(int i=1;i<tam;i++){
        for(int j=1;j<tam;j++){
            if (listaNo[i] != NULL ) matriz[i][j] = listaNo[Hash(i)]->getPeso(j);
        }
    }

    for(int k=0;k<tam;k++){
        for(int i=0;i<tam;i++){
            for(int j=0;j<tam;j++){
                if ((matriz[i][k] * matriz[k][j] != 0) && (i != j)){
                    if ((matriz[i][k] + matriz[k][j] < matriz[i][j]) || (matriz[i][j] == 0)){
                        matriz[i][j] = matriz[i][k] + matriz[k][j];
                    }
                }
            }
        }
    }
    cout<<endl;
    //cout<<"olá!"<<endl;
    cout<<"Matriz de Floyd:"<<endl<<endl<<"\t";
    for(int j=1;j<tam;j++)cout<<j<<"\t";
    cout<<endl;
    for (int i = 1; i <tam; i++){
        cout<<"\n"<<i<<"\t";
        for (int j = 1; j <tam; j++){
            cout<<matriz[i][j]<<"\t";
        }

    }
}

void Grafo::desmarcar(){
    int tam = nNos;
    for(int i=1;i<=tam;i++){
        listaNo[Hash(i)]->explorado=false;
    }
}
