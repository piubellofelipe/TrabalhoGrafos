#include <iostream>
#include <stdlib.h>
#include "Grafo.h"
#include <fstream>
#include <string>
#include <sys/time.h>




int main()
{




    string entradas[10];
    //pequenas
    entradas[0] = "./instancias/pequenas/huck.col.txt";
    entradas[1] = "./instancias/pequenas/queen5_5.col.txt";
    entradas[2] = "./instancias/pequenas/queen6_6.col.txt";
    entradas[3] = "./instancias/pequenas/queen7_7.col.txt";
    //medias
    entradas[4] = "./instancias/medias/le450_15b.col.txt";
    entradas[5] = "./instancias/medias/le450_15c.col.txt";
    entradas[6] = "./instancias/medias/le450_15d.col.txt";
    //grandes
    entradas[7] = "./instancias/grandes/inithx.i.1.col.txt";
    entradas[8] = "./instancias/grandes/inithx.i.2.col.txt";
    entradas[9] = "./instancias/grandes/inithx.i.3.col.txt";


    Grafo *grafos[10];


/*
    for (int i=0; i<10; i++) {
        string saida = "reativo";
        char c = (i+1)+'0';
        saida.push_back(c);
        ofstream file(saida);

        for (int j=0; j<1; j++) {
            //cout<<i<<" "<<j<<endl;
            clock_t c1, c2;
            grafos[i] = new Grafo(false, entradas[i]);
            c1 = clock();
            grafos[i]->ColoracaoGulosoRand(0.25, 3);
            c2 = clock();
            file << "----------------------------" << endl;
            //file << "Seed: " << S.seed << endl;
            //file << "Alpha: " << S.alpha << endl;
            //file << "Numero de cores utilizadas: " << S.cores << endl;
            double segundos = ((c2-c1)*1000/CLOCKS_PER_SEC);
            cout<<segundos<<endl;
        }
    }

    /* float alpha = 0.25;
     for (int i=0; i<10; i++) {
         string saida = "saida";
         char c = (i+1)+'0';
         saida.push_back(c);
         ofstream file(saida);
         file << "Grau do grafo:" << grafos[i]->getGrauGrafo() << endl;
         file << "Numero de nós: " << grafos[i]->getNnos() << endl;
         file << "Numero de arestas: " << grafos[i]->getNArestas() << endl;

         for (int j = 0; j < 30; j++) {

             struct timeval Inicio, Fim;
             struct Solucao S;
             S = grafos[i]->ColoracaoGulosoRand(alpha, j);
             gettimeofday(&Inicio, NULL);
             grafos[i]->zeraCores();
             file << "----------------------------" << endl;
             file << "Seed: " << S.seed << endl;
             file << "Alpha: " << S.alpha << endl;
             file << "Numero de cores utilizadas: " << S.cores << endl;
             gettimeofday(&Fim, NULL);
             double segundos = Fim.tv_sec - Inicio.tv_sec;
             double microssegundos = Fim.tv_usec - Inicio.tv_sec;
             double milissegundos = segundos*1000 + microssegundos/1000;
             file << "Tempo de execução: " << milissegundos << " milisegundos" << endl;

         }
         //grafos[i]->imprimeCorNo();
  
   }
*/
 */
 //    graphy->verificaColoracao();
//    graphy->imprimeCorNo();
//    graphy->Floyd();
//    graphy->buscaLargura(0,0);
//    graphy->ArvoreGerMinKruskel();
//    graphy->buscaLargura(1);
//    graphy->delNo(2);
//    graphy->imprimeNo();
//    graphy->imprimeGrauNo();
//    graphy->imprimeGrauGrafo();
//    graphy->kRegular();
//    graphy->completo();
//    graphy->seqGrauGrafo();
//    graphy->buscaProfundidade(2,0,0);
//    graphy->buscaLargura(2);

    return 0;
}
