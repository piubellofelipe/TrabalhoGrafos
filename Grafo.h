#include "No.h"
#ifndef GRAFO_H
#define GRAFO_H
#include <fstream>
#include <string>
#include <vector>
struct Solucao{
    int seed;
    double alpha;
    int cores;
};

class Grafo
{
public:

    struct Aresta2{
        int id1 = 0;
        int id2 = 0;
        int w = 0;
    };




    Grafo(bool temPeso, string arquivo);
    Grafo(int id, int tam);
    Grafo(int tam);
    ~Grafo();
    int getN(){return n;};
    int getNArestas(){return m;};
    int getNnos(){ return nNos;}
    int Hash(int Id);
    bool procuraNo(int Id);
    bool addNo(int Id);
    bool delNo(int Id);
    bool addAresta(int Id1, int Id2);
    bool addAresta(int Id1, int Id2, int w);
    bool delAresta();
    void setGrauGrafo(int Id);
    int getGrauGrafo(){return D;}
    void imprimeGrauGrafo(){cout<<"\nO grau do grafo é: "<<D<<endl;};
    int grauNo();
    void seqGrauGrafo();
    void ShellSort(int *vetor);
    void ShellSortArestas(Aresta2 vetor[]);
    void kRegular();
    void completo();
    void imprimeGrauNo();
    void imprimeNo();
    void imprimeCorNo();
    bool ehAdj(int Id1, int Id2);
    bool readFile(string txt, bool temPeso);
    void buscaProfundidade(int Id, int pai, int nivel);
    bool buscaProfundidade(int Id, int pai, int nivel, int buscando);
    bool buscaLargura(int Id,int Id2);
    Grafo ArvoreGerMinKruskel();
    void OrdenarA2(Aresta2 *vetor, int posicaoInicio, int posicaoFim);
    bool naoEstaContido(Aresta2 A2,Aresta2 S[]);
    Grafo SomaArvores(int G[], Aresta2 a2[]);
    Grafo addArvores(Grafo *G1, Grafo* G2, Aresta2 a2);
    void desmarcar();
    int ColoracaoGuloso();
    void ShellSort(No* num[]);
    int getCorDisponivelNo(int cores[],No* no);
    int getCorDisponivelAresta(int cores[], int id1, int id2);
    int verificaColoracao();
    struct Solucao GRA(int max_iter, int block_iter, double granularity, double gama, int seed);
    struct Solucao GRA2(int max_iter, int seed, int itr_bloco);
    int random(int tam, double *prob);
    No* getPrim(){
        return primeiro;}
    void Floyd();
    int AtualizaPos(float alpha, int tam, int seed);
    struct Solucao ColoracaoGulosoRand(double alpha, int seed);
    void zeraCores();
    void choose_alpha(vector<double> P, int rand, int &i);

        //void listaGrauNo();
    //Item 7
    //Getters e Setters

    No** listaNo;//lista de Nos


protected:
private:
    Grafo *ArvMin;
    No* primeiro;
    int n;// tamanho da tabela = numero de nós +1
    int nNos;
    int m;//numero de aresta
    bool flagDir;// direcionado ou nao
    int D;//grau do grafo

};

#endif // GRAFO_H