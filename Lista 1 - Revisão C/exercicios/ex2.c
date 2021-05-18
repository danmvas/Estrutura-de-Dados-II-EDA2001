//Dado um vetor de números inteiros v, retorne um novo vetor de forma que cada elemento no índice i seja o produto de todos os números na matriz original, com exceção de i.
#include "./lib/all.h"

int[] multiplicacaoValores(int *v){

    int lenght = sizeof(v) / sizeof(v[0]);
    int aux[];

    for (int j = 0; j < lenght; j++){
        int cabeca = v[j];

        for (int i = j+1; i < lenght; i++){
            if (cabeca + v[i] != k){
                continue;
            }
            else {
                printf("FOI PORRA\n");
                return int a[1,2];
            }
        }
    }

    printf("NAO FOI\n");
    return int a[1,2];
}