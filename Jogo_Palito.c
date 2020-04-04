/*
Jogo do sorteio de palitos utilizando pthreads:

N jogadores = N Threads

N palitos = Vetor[N] (Variável compartilhada com TODAS as Threads)

** Valores dos palitos:
						Devem ser > 0 e < 100.
						Devem ser gerados aleatóriamente.
**

Número de Jogadores = Número de Threads = Número de palitos = Tamanho do vetor N = N

A retirada dos palitos deve ser feita por exclusão mútua (Mutex).
Quanto um palito é retirado do vetor, deve ser inserido um valor igual a -1 na posição do palito retirado.
Após TODAS as threads "retiraram seus palitos", devem enviar para o processo principal cujo verificará qual o maior valor.

AS THREADS SÓ PODERÃO INICIAR O SORTEIO UMA VEZ QUE TODAS FOREM CRIADAS
*/

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

void main(){

    //Definição do idioma: Português
    setlocale(LC_ALL, "Portuguese");

    //Definição da quantidade de jogadores
    int qtd_jog;
    printf("Insira a quantidade de jogadores: ");
    scanf("%d", &qtd_jog);

    //Definição do vetor compartilhado (Palitos)
    int palitos[qtd_jog];

    //Função para gerar um valor aleatório para cada espaço do vetor compartilhado (palito)
    int i;
    for(i = 0; i < qtd_jog; i++){

        palitos[i] = 1 + rand() % 99;
    }

    //Função para imprimir os valores de cada espaço do vetor compartilhado (palito)
    for(i = 0; i < qtd_jog; i++){

        printf("%d: %d", i, palitos[i]);
        printf("\n");
    }

    //Função para retirar o palito e modificar o valor do espaço compartilhado para -1
    int thread;
    for(i = 0; i < qtd_jog;){
        
        if(i == -1){

            i++;
        }else{

            thread = palitos[i];
            palitos[i] = -1;
            //return thread;
        }
    }

    //Função para verificar o maior valor entre os palitos de cada thread
    //Quantidade de palitos = 5
    /*int maior = thread_1;
    for (i = 0; i < qtd_jog; i++){

    }*/    
}