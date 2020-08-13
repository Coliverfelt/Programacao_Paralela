#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<locale.h>

#define QTD_JOGADOR 7

typedef struct jogador{
	
	int jid;
	int palitoretirado;
} *Jogador;

int *palitos;
Jogador jogadores;
pthread_mutex_t mutexcomp;

void *retiraPalito(void *jogadorArg);

void main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	
	jogadores = (Jogador) malloc(QTD_JOGADOR * sizeof(Jogador));
	palitos = (int *) malloc(QTD_JOGADOR * sizeof(int));
	
	pthread_t *threads;
	threads = (pthread_t *) malloc(QTD_JOGADOR * sizeof(pthread_t));
	
	pthread_mutex_init(&mutexcomp, NULL);
	pthread_mutex_lock (&mutexcomp);
	
	int id;
	int i, rc;
	
	//Atribuindo valores aleatórios a cada palito
	for(i = 0; i < QTD_JOGADOR; i++){
		
		palitos[i] = rand() % 99 + 1;
	}
	
	//Cria thread retiraPalito passando um jogador como parâmetro
	for(id = 0; id < QTD_JOGADOR; id++){
		
		jogadores[id].jid = id;
		
		rc = pthread_create(&threads[id], NULL, retiraPalito, (void *) &jogadores[id]);
		
		if(rc){
			
			printf("\ERRO! pthread_create retornou %d.", rc);
			exit(-1);
		}
	}
	
	pthread_mutex_unlock(&mutexcomp);
	
	//Ponto de unção da threads
	for (i = 0; i < QTD_JOGADOR; i++){
		
    	pthread_join(threads[i], NULL);
  	}
	
	//Verifica qual é o maior palito
	int maiorvalor = jogadores[0].palitoretirado;
	
	for(id = 0; id < QTD_JOGADOR; id++){
		
		if(jogadores[id].palitoretirado > maiorvalor){
			
			maiorvalor = jogadores[id].palitoretirado;
		}
	}
	
	//Verifica quem é o vencedor
	printf("\n\n\nAutor: Caroline Oliveira Cavalcanti de Albuquerque");
	printf("\nMatrícula: 20131100105");
	printf("\nData de conclusão: 03/06/2020");
	printf("\n\n***********VENCEDOR(ES)***********");
	
	int podium = 0;
	
	for(id = 0; id < QTD_JOGADOR; id++){
		
		if(jogadores[id].palitoretirado == maiorvalor){
			
			podium++;
			printf("\n\n||%d. Jogador %d:\t Palito %d||", podium, jogadores[id + 1].jid, jogadores[id].palitoretirado);
		}
	}
	
	pthread_mutex_destroy(&mutexcomp);
	pthread_exit (NULL);
}

void *retiraPalito(void *jogadorArg){

	Jogador jogador = (Jogador *) jogadorArg;

	pthread_mutex_lock(&mutexcomp);
	
	srand(time(NULL));
	int indicepalito = rand() % QTD_JOGADOR;
	int valorpalito = palitos[indicepalito];
	
	while(valorpalito == -1){
	
		indicepalito = rand() % QTD_JOGADOR;
		valorpalito = palitos[indicepalito];
	}
	
	jogador->palitoretirado = palitos[indicepalito];
	palitos[indicepalito] = -1;
	
	pthread_mutex_unlock(&mutexcomp);

	pthread_exit(NULL);
}
