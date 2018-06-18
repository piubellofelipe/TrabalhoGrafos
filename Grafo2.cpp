#include "Grafo.h"
#include <math.h>
#include <limits>
#include <vector>
#include <time.h>

void Grafo::ShellSort(No* num[]){//ordena um vetor de nós pelo grau
    int i, flag=1, numLength = nNos;
    int d = numLength;
    No* temp;
    while (flag || (d>1)){
        flag = 0;
        d = (d+1)/2;
        for (i=0; i<(numLength - d); i++){
            if (num[i+d]->getGrau() > num[i]->getGrau()){
                temp = num[i+d];
                num[i+d] = num[i];
                num[i] = temp;
                flag = 1;
            }
        }

    }
    return;
}

int Grafo::ColoracaoGuloso() {
    //zeraCores();
    No* vetNos[nNos]; // vetor com a ordem dos nós a serem visitados, ordenados pelo grau
    int j=0;
    for (int i=0;i<n;i++){
        if (listaNo[i]!=NULL){
            vetNos[j]=listaNo[i];
            j++;
        }
    }
    ShellSort(vetNos); //ordena pelo grau


    //Agora com os nós ordenados, vamos colorir pelos de maior grau
    int cores[nNos];
    for (int i=0; i<nNos; i++){
        cores[i] = 0;
    }//a cor 0 indica que não está colorido, a.k.a a cor nao existe;

    for (int i =0; i<nNos; i++){
        if (vetNos[i]->cor == 0) vetNos[i]->cor = getCorDisponivelNo(cores, vetNos[i]);
        Aresta *aux = vetNos[i]->getAresta();
        while (aux != NULL){
            int id = aux->getId();
            if (listaNo[Hash(id)]->cor == 0)
                listaNo[Hash(id)]->cor = getCorDisponivelNo(cores, listaNo[Hash(id)]);
            aux = aux->getProx();
        }
        aux = vetNos[i]->getAresta();
        while (aux != NULL){
            if (aux->cor != 0){
                aux = aux->getProx();
                continue;
            }
            aux->cor = getCorDisponivelAresta(cores,vetNos[i]->getId(), aux->getId());
            No *no2 = listaNo[aux->getId()];
            Aresta *aux2 = no2->getAresta();
            while (aux2 != NULL){
                if (aux2->getId() == vetNos[i]->getId()){
                    aux2->cor = aux->cor;
                }
                aux2 = aux2->getProx();
            }
            aux = aux->getProx();
        }
    }

    for (int i=1; i<nNos; i++){
        if (cores[i] == 0){
            return i-1;
        }
    }


}

int Grafo::getCorDisponivelNo(int cores[],No* no){
    int i;
    for (i=1; cores[i] != 0; i++){
        Aresta *aux = no->getAresta();
        bool t = true;
        while (aux != NULL){
            int id = aux->getId();
            if (aux->cor == cores[i])
                t = false;
            if (listaNo[Hash(id)]->cor == cores[i]){
                t = false;
            }
            aux = aux->getProx();
        }
        if (t){
            return cores[i];
        }
    }
    if (cores[i] == 0){
        cores[i] = i;
        return cores[i];
    }
}

int Grafo::getCorDisponivelAresta(int cores[], int id1, int id2) {
    /*a cor da aresta precisa ser diferente da cor
        das suas pontas,e das arestas das suas pontas
     */
    int i;
    for (i=1; cores[i] != 0; i++){
        bool t = true;
        //cout<<cores[i]<<endl;
        if (listaNo[Hash(id1)]->cor == cores[i])
            t = false;
        else if (listaNo[Hash(id2)]->cor == cores[i])
            t = false;
        Aresta* aux = listaNo[Hash(id1)]->getAresta();
        while (aux != NULL){
            if (aux->cor == cores[i])
                t = false;
            aux = aux->getProx();
        }
        aux = listaNo[Hash(id2)]->getAresta();
        while (aux != NULL){
            if (aux->cor == cores[i])
                t = false;
            aux = aux->getProx();
        }

        if (t){
            return cores[i];
        }

    }
    if (cores[i] == 0){
        cores[i] = i;
        return i;
    }
}
int Grafo::verificaColoracao(){
    int maxCor=0;
    int k=0;
    for (int i=0; i<n; i++){
        if (listaNo[i] == NULL)
            continue;
        No *no = listaNo[i];
        int cor = no->cor;
        if (cor == 0){
            cout<<"O grafo não foi colorido corretamente!";
            k++;
            //return false;
        }
        if (cor > maxCor){
            maxCor = cor;
        }
        Aresta *aux = no->getAresta();
        while (aux != NULL){
            if (aux->cor == 0){
                cout<<"O grafo não foi colorido corretamente!";
                //return false;
                k++;
            }
            if (aux->cor > maxCor)
                maxCor = aux->cor;
            if (aux->cor == cor){
                cout<<"O grafo não foi colorido corretamente! "<<aux->cor<<" "<<cor<<" aresta"<<endl;
                //return false;

            }
            int id = aux->getId();
            No *no2 = listaNo[Hash(id)];
            if (no2->cor == cor){
                cout<<"O grafo não foi colorido corretamente! "<<no2->cor<<" "<<cor<<" no vizinho"<<endl;
                //return false;

            }
            Aresta *aux2 = no2->getAresta();
            while (aux2 != NULL){
                if (aux->cor == aux2->cor && aux2->getId() != no->getId() && aux->getId() != no2->getId()){
                    cout<<"O grafo não foi colorido corretamente! "<<aux->cor<<" "<<aux2->cor<<" aresta adjacente"<<endl;
                    //return false;
                }

                aux2 = aux2->getProx();
            }

            aux = aux->getProx();
        }

    }
    return maxCor;
}

struct Solucao Grafo::ColoracaoGulosoRand(double alpha, int seed) {
    zeraCores();
    struct Solucao S;
    S.alpha = alpha;
    S.seed = seed;
    No* vetNos[nNos]; // vetor com a ordem dos nós a serem visitados, ordenados pelo grau
    int j=0;
    for (int i=0;i<n;i++){
        if (listaNo[i]!=NULL && listaNo[i]->getId()!=0){
            //cout<<listaNo[i]->getId()<<endl;
            vetNos[j]=listaNo[i];
            j++;
        }
    }
    ShellSort(vetNos); //ordena pelo grau




    int cores[nNos];
    for (int i=0; i<nNos; i++){
        cores[i] = 0;
    }//a cor 0 indica que não está colorido, a.k.a a cor nao existe;

    //cout<<vetNos[0]->getId()<<endl;
    int tamanho = nNos;
    for (j =0; j<nNos; j++){
        //cout<<vetNos[0]->getId()<<endl;
        //cout<<j<<endl;
        int pos = AtualizaPos(alpha, tamanho, seed);
        //cout<<vetNos[pos]->getId()<<endl;
        int id = vetNos[pos]->getId();
        if (vetNos[pos]->cor == 0) vetNos[pos]->cor = getCorDisponivelNo(cores, vetNos[pos]);
        Aresta *aux = vetNos[pos]->getAresta();
        while (aux != NULL){
            aux->cor = getCorDisponivelAresta(cores, aux->getId(), id);
            aux = aux->getProx();
        }
        /*while (aux != NULL){
            int id = aux->getId();
            if (listaNo[Hash(id)]->cor == 0)
                listaNo[Hash(id)]->cor = getCorDisponivelNo(cores, listaNo[Hash(id)]);
            aux = aux->getProx();
        }

        aux = vetNos[pos]->getAresta();
        while (aux != NULL){
            if (aux->cor != 0){
                aux = aux->getProx();
                continue;
            }
            aux->cor = getCorDisponivelAresta(cores,id, aux->getId());
            No *no2 = listaNo[Hash(aux->getId())];
            Aresta *aux2 = no2->getAresta();

            while (aux2 != NULL){
                if (aux2->getId() == id){
                    aux2->cor = aux->cor;
                }
                aux2 = aux2->getProx();
            }
            aux = aux->getProx();
        }
        */
        for(int i=pos;i<tamanho;i++){
            vetNos[i]=vetNos[i+1];
        }

        tamanho = tamanho - 1;
    }
    for (int i=1; i<nNos; i++){
        if (cores[i] == 0){
            S.cores = i-1;
            break;
        }
    }
    return S;

}

int Grafo::AtualizaPos(float alpha, int tamanho, int seed) {

    srand(seed);

    int max = (int) (alpha*tamanho);
    if (max == 0) return 0;
    int aleatorio = (int) rand() % max;
    return aleatorio;


}

void Grafo::zeraCores() {
    for (int i=0; i<n; i++){
        if (listaNo[i] != NULL){
            listaNo[i]->cor = 0;
            Aresta *aux = listaNo[i]->getAresta();
            while (aux != NULL){
                aux->cor = 0;
                aux = aux->getProx();
            }
        }

    }
}



struct Solucao Grafo::GRA2(int max_iter, int seed, int itr_bloco) {
    zeraCores();
    struct Solucao melhor, S;
    melhor.cores = INFINITY;
    double prob[10];
    double alphas[10];
    double somQ=0.0;
    int valoresEncontrados[10];
    double media[10];
    int nAlfa[10];
    int nblocos =0;
    int gama =10;
    int embloco = 1;
    double q[10];
    int indice;
    double alpha;
    for (int i=0; i<10; i++){
        prob[i] = 1/10;
        alphas[i] = i*0.05;
        valoresEncontrados[i] = 0;
        media[i] = 0.0;
        nAlfa[i] = 0;
        q[i] = 0.0;
    }

    for (int it =0; it<max_iter; it++){
        if(it <= 10)
        {
            alpha = alphas[it-1];
            nAlfa[it-1]++;
        }
        else {
            indice = random(10, prob);
            alpha = alphas[indice];
            nAlfa[indice]++;
        }
        S = ColoracaoGulosoRand(alpha, seed);
        valoresEncontrados[indice]+=S.cores;
        if (S.cores <= melhor.cores) {
            melhor = S;
        }
        if(it == itr_bloco*embloco)
        {
            embloco++;
            for(int i = 0; i<10; i++)
            {

                if(nAlfa[i]!= 0)
                {
                    media[i] = (valoresEncontrados[i]*1.0)/nAlfa[i];
                    q[i] = (melhor.cores*1.0)/media[i];
                }
                else
                {
                    media[i] = 0.0;
                    q[i] = 0.0;
                }
            }
            somQ = 0.0;
            for(int i = 0; i<10;i++)
                somQ = q[i] + somQ;
            for(int i = 0; i<10; i++)
            {
                if(somQ!= 0.0)
                    prob[i] = (q[i]*1.0)/somQ;
                else
                    prob[i] = 0.0;
            }
        }
    }
    return melhor;

}

int Grafo::random(int tam, double *prob){
    int soma = 0;
    int nRand = 0;
    for (int i=0; i<tam; i++){
        soma += prob[i]*1000;
    }
    nRand = (soma >0)?rand() % soma:0;
    soma = 0;
    for (int i=0; i<tam; i++){
        soma+=prob[i]*1000;
        if (nRand <= soma){
            return i;
        }
    }
}

