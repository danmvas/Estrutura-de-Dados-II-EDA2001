//Dado um vetor de números inteiros v de tamanho n e um número k,
//retorne verdadeiro se a soma de qualquer par de números em v for igual a k.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool somaDePares(int *v, int k){

    int lenght = sizeof(v) / sizeof(v[0]);

    for (int j = 0; j < lenght; j++){
        int cabeca = v[j];

        for (int i = j+1; i < lenght; i++){
            if (k == cabeca + v[i]){
                printf("FOI PORRA\n");
                return true;
            }
        }
    }

    printf("NAO FOI\n");
    return false;
}