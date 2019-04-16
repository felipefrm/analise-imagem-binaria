#include <stdio.h>
#include <stdlib.h>
#include "paradigma.h"
#include "entradaSaida.h"

int forcaBruta(int **mat, int tamanhoMatriz, Ponto* inicial){
  int maior = 0, clock = 0, sub_matriz;
  for (int i=0; i<tamanhoMatriz; i++){
    for (int j=0; j<tamanhoMatriz; j++){
      if ((sub_matriz = submatrizValida(i, j, mat, &clock, maior, tamanhoMatriz)) > maior) {
        maior = sub_matriz;
        inicial->x = i;
        inicial->y = j;
      }
    }
  }
  return maior;
}

int submatrizValida(int i, int j, int **mat, int *clock, int maior, int tamanhoMatriz){
  int range = maior + 1;
  int i_range, j_range;
                                          // pega a maior submatriz possivel a partir do ponto [i][j]
  while (1) {
    i_range = range + i;
    j_range = range + j;

    if (i_range > tamanhoMatriz || j_range > tamanhoMatriz)
      return maior;

    if (!checkSubMatrizForcaBruta(mat, i, j, range)){
      return maior;
    }
    // for (int lin = i; lin < i_range; lin++){
    //
    //   for (int col = j; col < j_range; col++){
    //     (*clock)++;
    //     // printf("contador: %d\n", *clock);
    //     if (mat[lin][col] == 0){
    //       return maior;
    //     }
    //   }
    // }

    maior = range;
    range++;
  }

  return maior;
}


int guloso(int **mat, int tamanhoMatriz, Ponto* inicial){

  for (int maior = tamanhoMatriz; maior > 0; maior--){
    int ContadorAnda = tamanhoMatriz - maior + 1;
    for (int i = 0; i < ContadorAnda; i++){
      for (int j = 0; j < ContadorAnda; j++){
        if (checkSubMatrizGuloso(mat, i, j, maior)){
          inicial->x = i;
          inicial->y = j;
          return maior;
        }
      }
    }
  }
}

int dinamica(int **matriz,int tamanhoMatriz,Ponto* inicial){
  int i,j,maior = 0;
  int matAux[tamanhoMatriz+1][tamanhoMatriz+1];
  for(i=0;i<tamanhoMatriz+1;i++){
    matAux[0][i] = 0;
    matAux[i][0] = 0;
  }

  for(i=1;i<tamanhoMatriz+1;i++){
    for(j=1;j<tamanhoMatriz+1;j++){
      if(!matriz[i-1][j-1])
          matAux[i][j] = 0;
      else{
        matAux[i][j] = 1 + minimo(matAux[i-1][j],matAux[i][j-1],matAux[i-1][j-1]);
        if(matAux[i][j] > maior){
          maior = matAux[i][j];
          inicial->x = i-maior;
          inicial->y = j-maior;
        }
      }
    }
  }
  return maior;
}
int minimo(int x, int y, int z){
  if(x < y && x < z)
    return x;
  if(y < x && y < z)
    return y;
  if(z < x && z < y)
    return z;
  return x;
}
