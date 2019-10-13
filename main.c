#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graph{
    int V;
    int A;
    int **M;
    int *custos;
}*Graph;

int **alocaMatriz(int r, int c){
	/* A fun��o retorna uma matriz de incid�ncias com
	r linhas (numero de v�rtices) e c colunas (numero
	de arestas) e preenche os espa�os com zero. 
	*/
    int i, j;
    int **m = malloc(r * sizeof(int *));
    if(m == NULL) return NULL; //mem�ria insuficiente
        for (i = 0; i < r; i++){
            m[i] = malloc((c * sizeof(int)));
            if(m[i] == NULL){ //memoria insuficiente
            	for(j = 0; j < i; j++) free(m[j]);
            	free(m);
            	return NULL;
        	}
        }
    for(i = 0; i < r; i++) //preenchendo os espa�os com zero
        for(j = 0; j < c; j++)
            m[i][j] = 0;

    return m;
}//alocaMatriz()

void GRAPHInsert(Graph G, int u, int v, int c, int custo){
	/* A fun��o insere uma aresta uv na matriz de incid�ncias
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
        //Remove o �ltimo caractere do caminho, pois o fgets armazena a quebra de linha '\n'
        char *p_chr = strchr(caminhoDoArquivo, '\n');
        if(p_chr != NULL)
            *p_chr = '\0';
        arquivo = fopen(caminhoDoArquivo, "r");
    }
    fscanf(arquivo, "%d %d", &G->V, &G->A); //L� a primeira linha do arquivo
    G->M = alocaMatriz(G->V, G->A);
    if(G->M == NULL) return NULL; //mem�ria insuficiente
    
	G->custos = malloc(sizeof(int) * G->A);
    if(G->custos == NULL) return NULL; //mem�ria insuficiente
    for(i = 0; i < G->A; i++){
    	fscanf(arquivo, "%d %d %d", &u, &v, &custo);
		GRAPHInsert(G, u, v, i, custo); 
	}
	fclose(arquivo);
    return G;
}

int naFronteira(int *front, int a){
	int i;
	for(i = 0; i < a; i++)
		if(front[i] == 1)
			return 1;
	return 0;
}

int arestaCustoMinimo(int *front, int *z, int *custos, int a, int v){
	int i;
	for(i = 0; i < a; i++){
		
	}
}

void algPrim(Graph G){
	int z[G->V], front[G->A], i, totalCusto = 0;
	for(i = 0; i < G->V; i++)
		z[i] = 0;
	for(i = 0; i < G->A; i++)
		front[i] = 0;
	z[0] = 1;
	for(i = 0; i < G->A; i++)
		if(G->M[1][i] == 1)
			front[i] = 1;
	while(naFronteira(front, G->A)){
		
	}
}

int main() {
    //Graph G = GRAPHInit();
    int a = 5;
    int front[5] = {0, 0, 0, 0, 0};
    if(naFronteira(front, a)) printf("tem aresta na fronteira");
    else printf("n�o tem fronteira");
    
    
    return 0;
}
