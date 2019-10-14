/*1º Exercício-Programa de Grafos
 * Prof.: Glauber Cintra
 * Equipe: Francisco Lucas Lima da Silva
 *         José Alcides Mendes da Silva Júnior
 *         Juliana Silva Cardoso
 *         Rodrigo Alonso Caldas
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Graph{
    int V; //Número de vértices de G
    int A; //Número de arestas de G
    int **M; //Matriz de adjacências de G
}*Graph;

int **alocaMatriz(int v){
    /* A função retorna uma matriz de adjacências v x v,
     * onde v é o número de vértices de G.
     * e preenche os espaços com infinito.
    */
    int i, j;
    int **m = malloc(v * sizeof(int *));
    if(m == NULL) return NULL; //memória insuficiente
    for (i = 0; i < v; i++){
        m[i] = malloc((v * sizeof(int)));
        if(m[i] == NULL){ //memória insuficiente
            for(j = 0; j < i; j++) free(m[j]);
            free(m);
            return NULL;
        }
    }
    for(i = 0; i < v; i++) //preenchendo os espaços com zero
        for(j = 0; j < v; j++)
            m[i][j] = INT_MAX;

    return m;
}//alocaMatriz()

void GRAPHInsert(Graph G, int u, int v, int custo){
    /* A função insere uma aresta uv na matriz de incidências
     * e guarda o custo da aresta no vetor de custos.
    */
    if(G->M[u][v] != custo || G->M[v][u] != custo){ //Verifica se já não há tal aresta
        G->M[u][v] = custo;
        G->M[v][u] = custo;
    }
}//GRAPHInsert()

Graph GRAPHInit(){
    /* A função lê um arquivo que contém o número de vértices e
     * de arestas de G, as arestas uv de G e seus respectivos custos.
    */
    Graph G = malloc(sizeof (*G)); //Ponteiro para G
    FILE *arquivo = NULL;
    char caminhoDoArquivo[50];
    int i, u, v, custo; //Váriáveis para laço e váriaveis para criar G

    while(arquivo == NULL){
        printf("Insira o caminho do arquivo e pressione Enter: \n");
        fgets(caminhoDoArquivo, sizeof(caminhoDoArquivo), stdin);
        //Remove o último caractere do caminho, pois o fgets armazena a quebra de linha '\n'
        char *p_chr = strchr(caminhoDoArquivo, '\n');
        if(p_chr != NULL)
            *p_chr = '\0';
        arquivo = fopen(caminhoDoArquivo, "r");
    }
    fscanf(arquivo, "%d %d", &G->V, &G->A); //Lê a primeira linha do arquivo
    G->M = alocaMatriz(G->V); // Cria matriz V x V
    if(G->M == NULL) return NULL; //memória insuficiente

    for(i = 0; i < G->A; i++){
        fscanf(arquivo, "%d %d %d", &u, &v, &custo);
        GRAPHInsert(G, u-1, v-1, custo); //Insere as arestas uv no grafo e seus custos
    }
    fclose(arquivo);
    return G;
}//GRAPHinit()

int minValor(int chave[], bool z[], int V) {
    /* A função encontra o vértice com valor mínimo de chave, do conjunto de
     * vértices que ainda não estão em Z.
     * */
    int min = INT_MAX, min_index = 0, v;

    for (v = 0; v < V; v++){
        if (z[v] == false && chave[v] < min){
            min = chave[v];
            min_index = v;
        }
    }
    return min_index;
}//minValor()

bool conjZ(bool *z, int V){
    /* A função verifica se todos os vertices de G estão em Z.
     * Retorna true se possui algum vértice que não está em Z.
     * Retorna false se todos os vértices estão em Z.
     * */
    int v;
    for(v = 0; v < V; v++){
        if(!z[v]) return true;
    }
    return false;
}//conjZ()

void printArvore(int *ant, int *chave, int V){
    /* A função imprime a árvore geradora mínima construída pelo
    algoritmo de Prim.
    */
    int i, custo = 0;
    printf("\nArvore geradora minima: ");
    for(i = 1; i < V; i++){
        printf("(%d, %d) ", ant[i]+1, i+1);
        custo += chave[i];
    }
    printf("\nCusto: %d", custo);
}//printArvore()

void algPrim(Graph G){
    /* A função constroi e imprime uma árvore geradora minima (AGM)
     * para um grafo G representado por uma matriz de adjacências
     * */
    int ant[G->V]; //Vetor para armazenar a AGM
    int chave[G->V]; //Vetor que armazena os custos mínimos da fronteira de cada vértice
    bool z[G->V]; //Vetor que armazena os vértices inseridos no conjunto Z
    int i, j, v;

    for(i = 0; i < G->V; i++) { //Iniciando vetores
        z[i] = false;
        chave[i] = INT_MAX;
    }

    //O vértice 0 será a raiz da AGM
    chave[0] = 0;
    ant[0] = -1;

    //Enquanto existir vértice não inserido em Z
    while(conjZ(z, G->V)){
        int u = minValor(chave, z, G->V); //Busca o indice com aresta de menor custo na fronteira
        z[u] = true; //Insere u em Z

        //Atualize o valor da chave e o índice anterior dos vértices adjacentes ao vértice selecionado.
        //Considere apenas os vértices que ainda não estão incluídos na AGM
        for(v = 0; v < G->V; v++){
            //O grafo[u][v] é diferente de zero apenas para vértices adjacentes de m
            //z[v] é falso para vértices ainda não incluídos na AGM
            //Atualize a chave apenas se o grafo[u][v] for menor que chave[v]
            if(G->M[u][v] && z[v] == false && G->M[u][v] <= chave[v]){
                ant[v] = u;
                chave[v] = G->M[u][v];
            }
        }
    }
    //Ao final, imprime a AGM construída
    printArvore(ant, chave, G->V);
}//algPrim()

int main() {
    
    Graph G = GRAPHInit();

    algPrim(G);

    return 0;
}//main()
