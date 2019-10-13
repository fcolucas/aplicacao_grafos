#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h> 

typedef struct Graph{
    int V;
    int A;
    int **M;
    int *custos;
}*Graph;

int **alocaMatriz(int r, int c){
	/* A função retorna uma matriz de incidências com
	r linhas (numero de vértices) e c colunas (numero
	de arestas) e preenche os espaços com zero. 
	*/
    int i, j;
    int **m = malloc(r * sizeof(int *));
    if(m == NULL) return NULL; //memória insuficiente
    for (i = 0; i < r; i++){
        m[i] = malloc((c * sizeof(int)));
        if(m[i] == NULL){ //memoria insuficiente
        	for(j = 0; j < i; j++) free(m[j]);
        	free(m);
        	return NULL;
    	}
    }
    for(i = 0; i < r; i++) //preenchendo os espaços com zero
        for(j = 0; j < c; j++)
            m[i][j] = 0;

    return m;
}//alocaMatriz()

void GRAPHInsert(Graph G, int u, int v, int c, int custo){
	/* A função insere uma aresta uv na matriz de incidências
	e guarda o custo da aresta no vetor de custos.
	*/
	if(G->M[u][c] != 1 || G->M[v][c] != 1){
		G->M[u][c] = 1;
		G->M[v][c] = 1;
		G->custos[c] = custo;
	}
}//GRAPHInsert()

Graph GRAPHInit(){
    Graph G = malloc(sizeof (*G));
    FILE *arquivo = NULL;
    char caminhoDoArquivo[50];
    int i, u, v, custo;

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
    G->M = alocaMatriz(G->V, G->A);
    if(G->M == NULL) return NULL; //memória insuficiente
    
	G->custos = malloc(sizeof(int) * G->A);
    if(G->custos == NULL) return NULL; //memória insuficiente
    for(i = 0; i < G->A; i++){
    	fscanf(arquivo, "%d %d %d", &u, &v, &custo);
		GRAPHInsert(G, u-1, v-1, i, custo);
	}
	fclose(arquivo);
    return G;
}

int minValor(int chave[], bool z[], int V) 
{ 
    // Initialize min value 
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
	int v;
	for(v = 0; v < V; v++){
		if(!z[v]) return true;
	}
	return false;
}

void printArvore(int *ant, int *chave, int V){
	int i, custo = 0; 
	printf("Arvore geradora minima: ");
	for(i = 1; i < V; i++){
		printf("(%d, %d) ", ant[i]+1, i+1);
		custo += chave[i];
	}
	printf("\nCusto: %d", custo);
}

void algPrim(Graph G){
	int ant[G->V];
	int chave[G->V];
	bool z[G->V];
	int i, v, a;
	
	for(i = 0; i < G->V; i++) {
		z[i] = false;
		chave[i] = INT_MAX;
	}
	
	chave[0] = 0;
	ant[0] = -1;
	
	while(conjZ(z, G->V)){
		int u = minValor(chave, z, G->V);
		printf("%d \n", u);
		z[u] = true;
		
		for(a = 0; a < G->A; a++){
			for(v = 0; v < G->V; v++){
				if(z[v] == false && 
				G->M[u][a] == G->M[v][a] == 1 && 
				G->custos[a] < chave[v]){
					ant[v] = u; 
					chave[v] = G->custos[a];
				}
			}
		}
	}
	printArvore(ant, chave, G->V);	
}

int main() {
    //int i;
	Graph G = GRAPHInit();
//	if(G == NULL) printf("n tem grafo");
//	printf("(V = %d; A = %d)\n", G->V, G->A);
//	for(i = 0; i < G->A; i++)
//		printf("%d ", G->custos[i]);
	algPrim(G);
    
    return 0;
}
