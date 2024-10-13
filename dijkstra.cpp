#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <limits.h>



#define N 5

void definir_letras(char alfabeto[N]) {
    for (int i = 0; i < N; i++)
    {
        alfabeto[i] = 97 + i;
    }
    
}
void dijkstra(int matriz[N][N], char vertices[N]) {
    int distancia[N];
    int indice_previo[N];
    int vs[N]; // indice nodo visitado
    bool visitado[N] = {false};
    // Inicializando datos
    for (int i = 0; i < N; i++) {
        distancia[i] = INT_MAX; //Distancias a infinito
        indice_previo[i] = -1;
    }
    
    distancia[0] = 0;

    for (int i = 0; i < N - 1; i++) {
        //Variables auxiliares
        int aux_min_ind = -1;
        //Partimos desde la distancia maxima
        int aux_min_dist = INT_MAX;

        for (int v = 0 ; v < N; v++) {
            int h = vs[v];
            if (visitado[v] == false && distancia[v] < aux_min_dist) {
                aux_min_dist = distancia[v];
                aux_min_ind = v;
            }
        }

        vs[i] = aux_min_ind; //marca posicion ya visitada
        visitado[aux_min_ind] = true; //marca que ya paso por ese nodo
        //busca el nodo correspondiente
        for (int v = 0; v < N; v++) {
            if (matriz[aux_min_ind][v] != -1 && visitado[v] == false && distancia[aux_min_ind] + matriz[aux_min_ind][v] < distancia[v]) {
                distancia[v] = distancia[aux_min_ind] + matriz[aux_min_ind][v];
                indice_previo[v] = aux_min_ind;
            }
        }
    }
    std::cout << "El orden de los nodos es: " << std::endl;
    for (int i = 0; i < N; i++) {
        int h = vs[i];
        int l = vs[i + 1];
        std::cout << vertices[h] << " -> " << vertices[l] << std::endl;
    }
}

void imprimir_grafo(int matriz[N][N], char vector[N]) {
  int i, j;
  FILE *fp;
  
  fp = fopen("grafo.txt", "w");
  fprintf(fp, "%s\n", "digraph G {");
  fprintf(fp, "%s\n", "graph [rankdir=LR]");
  fprintf(fp, "%s\n", "node [style=filled fillcolor=yellow];");
  
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      // evalua la diagonal principal.
      if (i != j) {
        if (matriz[i][j] > 0) {
          fprintf(fp, "%c%s%c [label=%d];\n", vector[i],"->", vector[j], matriz[i][j]);
        }
      }
    }
  }
  
  fprintf(fp, "%s\n", "}");
  fclose(fp);

  system("dot -Tpng -ografo.png grafo.txt");
  system("eog grafo.png &");
}


int main(int argc, char **argv) {
//arreglo vertices y distancias
    char V[N];

  
//matriz M, lugares vacios representados con -1
  // valores de prueba1.
   int M[N][N] = {{ 0, 4, 11, -1, -1},
                 {-1, 0, -1,  6,  2},
                 {-1 ,3,  0,  6, -1},
                 {-1,-1, -1,  0, -1},
                 {-1,-1,  5,  3,  0}};
    // int M[N][N] = {{0,-1},
    //                {3,0}};
// llenando arreglo con los vertices
    definir_letras(V);

    dijkstra(M, V);

    imprimir_grafo(M,V);
    return 0;


    
}