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
void nodo_alternativo(int matriz[N][N], bool visitado,int indice, int vs[], int distancia[] ){
    int distancias[N];
    for (int i = 0; i < N; i++) 
    {
        //recupera todos los posibles caminos
        if (matriz[indice][i] != -1 && matriz[indice][i] != 0)
        {
            distancias[i] = matriz[indice][i];
        }
        else
        {
            distancias[i] = INT_MAX; 
        }
        
    }

    int distancia_max = INT_MIN;
    int indice_v_max = -1; 
    //Compara la fila con cada columna
    for (int i = 0; i < N; i++)
    {   
        if (distancias[i] > distancia_max && visitado == false )
        {
            distancia_max = distancias[i];
            indice_v_max = i;
        }
    }
    //devuelve la menor distancia y su indice
    if (indice_v_max != -1) {
        vs[indice] = indice_v_max;
        distancia[indice] = distancia_max;
    }
}

void compara_distancias(int matriz[N][N], bool visitado, int indice, int vs[], int distancia[] ){
    int distancias[N];
    for (int i = 0; i < N; i++) 
    {
        //recupera todos los posibles caminos
        if (matriz[indice][i] != -1 && matriz[indice][i] != 0)
        {
            distancias[i] = matriz[indice][i];
        }
        else
        {
            distancias[i] = INT_MAX; // lleva a infinito los indices que no conectan
        }
        
    }

    int distancia_min = INT_MAX;
    int indice_v_min = 0; 
    //Compara la fila con cada columna
    for (int i = 0; i < N; i++)
    {   
        if (visitado == false && distancias[i] < distancia_min )
        {
            distancia_min = distancias[i];
            indice_v_min = i;
        }
    }
    //devuelve la menor distancia y su indice
    vs[indice] = indice_v_min;
    distancia[indice] = distancia_min;
}

void prim(int matriz[N][N], char vertices[N]){
    int vs[N]; //arreglo indice de nodo visitado
    bool visitado[N] = {false}; // arreglo con el estado de cada nodo
    int distancia[N]; // arreglo distancia entre un nodo y el siguiente
    int i = 0;
    int h = 0;
    int c = 0;
    while ( c != N)
    {   
        compara_distancias(matriz, visitado[h], h, vs, distancia);
        h = vs[i];
        visitado[h] = true;
        if (distancia[h] == INT_MAX  || distancia[h] == INT_MIN)
        {
            if (h > 0 && i> 0 )
            {
                std::cout << "hola mundo";
                nodo_alternativo(matriz, visitado[h - 1], (h-1), vs, distancia);
                h = vs[i];
            }          
        }
  
        c = 0 ;
        for (int j = 0; j < N; j++)
        {
            if (visitado[j] == true)
            {
                c++;
            }
        }
        i++;
        
    }
            

    for (int i = 0; i < N; i++)
    {
        int h = vs[i];
        std::cout << "vertice: " << vertices[i] << " -- " << vertices[h] << ", distancias: " << distancia[i] << std::endl;
    }
    
    
}

void imprimir_grafo(int matriz[N][N], char vector[N]) {
  int i, j;
  FILE *fp;
  
  fp = fopen("grafo.txt", "w");
  fprintf(fp, "%s\n", "graph G {");
  fprintf(fp, "%s\n", "graph [rankdir=LR]");
  fprintf(fp, "%s\n", "node [style=filled fillcolor=yellow];");
  
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      // evalua la diagonal principal.
      if (i != j) {
        if (matriz[i][j] > 0) {
          fprintf(fp, "%c%s%c [label=%d];\n", vector[i],"--", vector[j], matriz[i][j]);
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
int M[N][N] =  {{0, 4, 11,-1,-1},
                {-1, 0,-1, 6, 2},
                {-1,-1, 0,  6,-1},
                {-1,-1,-1, 0,-1},
                {-1,-1,-1,-1, 0}};
    // int M[N][N] = {{0,-1},
    //                {3,0}};
// llenando arreglo con los vertices
    definir_letras(V);
    imprimir_grafo(M,V);

    prim(M, V);
}