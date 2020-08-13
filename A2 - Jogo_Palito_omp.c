#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>

typedef struct jogador{
	
	int id;
	int palitoretirado;
} *Jogador;

int main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	
	int nthreads, tid, value, quantidadejogadores, i;
	/*void omp_init_lock(omp_lock_t *lock);
	void omp_set_lock(omp_lock_t *lock);
	void omp_unset_lock(omp_lock_t *lock);
	void omp_destroy_lock(omp_lock_t *lock);*/
	
	omp_lock_t lock;	
	omp_init_lock(&lock);
	
	printf("\nQuantos jogadores vão jogar? ");
	scanf("%d", &quantidadejogadores);
	
	int *palitos = (int*) malloc(quantidadejogadores * sizeof(int));;
	Jogador jogador = (Jogador) malloc(quantidadejogadores * sizeof(Jogador));
	
	for(i = 0; i < quantidadejogadores; i++){
		
		palitos[i] = rand() % 99 + 1;
		printf("\nPalito[%d] = %d.", i, palitos[i]);
	}
		
	/* Divide em um conjunto de threads, cada uma com suas próprias variáveis. */
	#pragma omp parallel shared(palitos, lock) private(tid) num_threads(quantidadejogadores)
	{
		nthreads = omp_get_num_threads(); // Função que retorna a quantidade de threads.'
		tid = omp_get_thread_num(); // Função que retorna o ID da thread.'
		
		jogador[tid].id = tid;
		printf("\nJogador %d: %d", tid, jogador[tid].id);
		
		omp_set_lock(&lock);
		
		srand(time(NULL));
    	int indicepalito = rand() % nthreads;
		int valorpalito = palitos[indicepalito];
		
		while(valorpalito == -1){
			
			indicepalito = rand() % nthreads;
			valorpalito = palitos[indicepalito];
		}
		
		jogador[tid].palitoretirado = palitos[indicepalito];
		palitos[indicepalito] = -1;
		
		omp_unset_lock(&lock);
	} /* Aqui, todas as threads se juntam ao processo principal e encerram. */
	
	int maiorvalor = 0;
	//Verifica qual é o maior palito
	for(i = 0; i < quantidadejogadores; i++){
		
		if(jogador[i].palitoretirado > maiorvalor){
			
			maiorvalor = jogador[i].palitoretirado;
		}
	}
		
	//Verifica quem é o vencedor
	printf("\n\n\nAutor: Caroline Oliveira Cavalcanti de Albuquerque");
	printf("\nMatrícula: 20131100105");
	printf("\nData de conclusão: 06/06/2020");
	printf("\n\n***********VENCEDOR(ES)***********");
	
	int podium = 0;
	
	for(i = 0; i < quantidadejogadores; i++){
		
		if(jogador[i].palitoretirado == maiorvalor){
			
			podium++;
			printf("\n\n||%d. Jogador %d:\t Palito %d||", podium, jogador[i + 1].id, jogador[i].palitoretirado);
		}
	}
	omp_destroy_lock(&lock);
}
