//Dado um vetor de números inteiros v de tamanho n e um número k, retorne verdadeiro se a soma de qualquer par de números em v for igual a k.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool somaDePares(int *v, int k){

    int j = 0; cabeca = v[j];
    int lenght = sizeof(v) / sizeof(v[0]);

    for (j; j < lenght; j++){

        for (int i = 1; i < lenght; i++){
            if (k = cabeca + i)
             return true;

         else i++;
        }
    
    }

    return false;
}