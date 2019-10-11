#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graph{
    int V;
    int A;
    int **M;
    int *custos;
}*Graph;

int **MATRIXint(int r, int c){
    int i, j;
    int **m = malloc(r * sizeof(int *));
    if(m != NULL) {
        for (i = 0; i < r; i++)
            m[i] = malloc((c * sizeof(int)));
    }
    for(i = 0; i < r; i++)
        for(j = 0; j < c; j++)
            m[i][j] = 0;

    return m;
}

void GRAPHInsert(Graph G, int u, int v, int c, int custo){
	if(G->M[u][c] != 1 || G->M[v][c] != 1){
		G->M[u][c] = 1;
		G->M[v][c] = 1;
		G->custos[c] = custo;
	}
}

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
    G->M = MATRIXint(G->V, G->A);
    G->custos = malloc(sizeof(int) * G->A);
    if(G->custos != NULL){
	    for(i = 0; i < G->A; i++){
	    	fscanf(arquivo, "%d %d %d", &u, &v, &custo);
			GRAPHInsert(G, u, v, i, custo); 
		}
	}
    return G;
}

int main() {
    Graph G = GRAPHInit();
    int i;
    
    printf("%d, %d", G->V, G->A);
    for(i = 0; i < G->A; i++)
    	printf("%d ", G->custos[i]);
    return 0;
}
