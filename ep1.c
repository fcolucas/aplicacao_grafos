/*1� Exerc�cio-Programa de Grafos
 * Prof.: Glauber Cintra
 * Equipe: Francisco Lucas Lima da Silva
 *         Jos� Alcides Mendes da Silva J�nior
 *         Juliana Silva Cardoso
 *         Rodrigo Alonso Caldas
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Graph{
    int V; //N�mero de v�rtices de G
    int A; //N�mero de arestas de G
    int **M; //Matriz de incid�ncias de G
}*Graph;

int **alocaMatriz(int r){
    /* A fun��o retorna uma matriz de adjac�ncias r x r,
     * onde r � o n�mero de v�rtices de G.
     * e preenche os espa�os com zero.
    */
    int i, j;
    int **m = malloc(r * sizeof(int *));
    if(m == NULL) return NULL; //mem�ria insuficiente
    for (i = 0; i < r; i++){
        m[i] = malloc((r * sizeof(int)));
        if(m[i] == NULL){ //mem�ria insuficiente
            for(j = 0; j < i; j++) free(m[j]);
            free(m);
            return NULL;
        }
    }
    for(i = 0; i < r; i++) //preenchendo os espa�os com zero
        for(j = 0; j < r; j++)
            m[i][j] = INT_MAX;

    return m;
}//alocaMatriz()

void GRAPHInsert(Graph G, int u, int v, int custo){
    /* A fun��o insere uma aresta uv na matriz de incid�ncias
     * e guarda o custo da aresta no vetor de custos.
    */
    if(G->M[u][v] != custo || G->M[v][u] != custo){ //Verifica se j� n�o h� tal aresta
        G->M[u][v] = custo;
        G->M[v][u] = custo;
    }
}//GRAPHInsert()

Graph GRAPHInit(){
    /* A fun��o l� um arquivo que cont�m o n�mero de v�rtices e
     * de arestas de G, as arestas uv de G e seus respectivos custos.
    */
    Graph G = malloc(sizeof (*G)); //Ponteiro para G
    FILE *arquivo = NULL;
    char caminhoDoArquivo[50];
    int i, u, v, custo; //V�ri�veis para la�o e v�riaveis para criar G

    while(arquivo == NULL){
        printf("Insira o caminho do arquivo e pressione Enter: \n");
        fgets(caminhoDoArquivo, sizeof(caminhoDoArquivo), stdin);
        //Remove o �ltimo caractere do caminho, pois o fgets armazena a quebra de linha '\n'
        char *p_chr = strchr(caminhoDoArquivo, '\n');
        if(p_chr != NULL)
            *p_chr = '\0';
        arquivo = fopen(caminhoDoArquivo, "r");
    }
    fscanf(arquivo, "%d %d", &G->V, &G->A); //L� a primeira linha do arquivo
    G->M = alocaMatriz(G->V); // Cria matriz V x V
    if(G->M == NULL) return NULL; //mem�ria insuficiente

    for(i = 0; i < G->A; i++){
        fscanf(arquivo, "%d %d %d", &u, &v, &custo);
        GRAPHInsert(G, u-1, v-1, custo); //Insere as arestas uv no grafo e seus custos
    }
    fclose(arquivo);
    return G;
}

int minValor(int chave[], bool z[], int V) {
    /* A fun��o encontra o v�rtice com valor m�nimo de chave, do conjunto de
     * v�rtices que ainda n�o est�o em Z.
     * */
    int min = INT_MAX, min_index = 0, v;

    for (v = 0; v < V; v++){
        if (z[v] == false && chave[v] < min){
            min = chave[v];
            min_index = v;
        }
    }
    return min_index;
}

bool conjZ(bool *z, int V){
    /* A fun��o verifica se todos os vertices de G est�o em Z.
     * Retorna true se possui algum v�rtice que n�o est� em Z.
     * Retorna false se todos os v�rtices est�o em Z.
     * */
    int v;
    for(v = 0; v < V; v++){
        if(!z[v]) return true;
    }
    return false;
}

void printArvore(int *ant, int *chave, int V){
    /* A fun��o imprime a �rvore geradora m�nima constru�da pelo
    algoritmo de Prim.
    */
    int i, custo = 0;
    printf("\nArvore geradora minima: ");
    for(i = 1; i < V; i++){
        printf("(%d, %d) ", ant[i]+1, i+1);
        custo += chave[i];
    }
    printf("\nCusto: %d", custo);
}

void algPrim(Graph G){
    /* A fun��o constroi e imprime uma �rvore geradora minima (AGM)
     * para um grafo G representado por uma matriz de adjac�ncias
     * */
    int ant[G->V]; //Vetor para armazenar a AGM
    int chave[G->V]; //Vetor que armazena os custos m�nimos da fronteira de cada v�rtice
    bool z[G->V]; //Vetor que armazena os v�rtices inseridos no conjunto Z
    int i, j, v;

    for(i = 0; i < G->V; i++) { //Iniciando vetores
        z[i] = false;
        chave[i] = INT_MAX;
    }

    //O v�rtice 0 ser� a raiz da AGM
    chave[0] = 0;
    ant[0] = -1;

    //Enquanto existir v�rtice n�o inserido em Z
    while(conjZ(z, G->V)){
        int u = minValor(chave, z, G->V); //Busca o indice com aresta de menor custo na fronteira
        z[u] = true; //Insere u em Z

        //Atualize o valor da chave e o �ndice anterior dos v�rtices adjacentes ao v�rtice selecionado.
        //Considere apenas os v�rtices que ainda n�o est�o inclu�dos na AGM
        for(v = 0; v < G->V; v++){
            //O grafo[u][v] � diferente de zero apenas para v�rtices adjacentes de m
            //z[v] � falso para v�rtices ainda n�o inclu�dos na AGM
            //Atualize a chave apenas se o grafo[u][v] for menor que chave[v]
            if(G->M[u][v] && z[v] == false && G->M[u][v] <= chave[v]){
                ant[v] = u;
                chave[v] = G->M[u][v];
            }
        }
    }
    //Ao final, imprime a AGM constru�da
    printArvore(ant, chave, G->V);
}

int main() {
    
    Graph G = GRAPHInit();

    algPrim(G);

    return 0;
}
