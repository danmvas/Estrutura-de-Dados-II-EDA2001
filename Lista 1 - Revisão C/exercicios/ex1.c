//Dado um vetor de números inteiros v de tamanho n e um número k,
//retorne verdadeiro se a soma de qualquer par de números em v for igual a k.

#include "../exercicios/all.h"

bool somaDePares(int *v, int k){
    
    printf("Resposta primeiro exercício: ");

    for (int j = 0; j < 5; j++){
        int cabeca = v[j];

        for (int i = j+1; i < 5; i++){
            if (k == cabeca + v[i]){
                printf("True\n");
                return true;
            }
        }
    }

    printf("False\n");
    return false;
}