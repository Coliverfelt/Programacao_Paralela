/*
2)Crie  um programa em linguagem C e Pthreads que pergunte ao usuário se ele deseja criar novas
threads (0 – Sim ou 1 - Não). O programa deve encerrar quando usuário digitar 2. Caso o usuário
decidir criar novas threads, uma função genérica qualquer deve ser executada por elas:
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdint.h>
#include<locale.h>

#define NUM_THREAD 1

struct thread_data{
	
	int thread_id;
};

void *criaThread(void *threadArg);

int main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	int threadcount = 0;
	int rc;
	
	while(1){
		
		printf("\nVocê deseja criar uma thread?");
		printf("\n0 - SIM");
		printf("\n1 - NÃO");
		printf("\n2 - SAIR");
		
		struct thread_data *threads_data;
		pthread_t *thread;
		int user = 0;
		scanf("%d", &user);
		
		switch(user){	
			case 0:
				
				threads_data = (struct thread_data *) malloc(sizeof(struct thread_data));
				threadcount++;
				
				thread = (pthread_t *) malloc(NUM_THREAD * sizeof(pthread_t));
				
				printf("\nCriando thread %d...", threadcount);
				threads_data->thread_id = threadcount;
				rc = pthread_create(thread, NULL, criaThread, (void *) threads_data);
				
				if(rc){
					
					printf("\nERRO! Return Code da pthread_create é %d.", rc);
					exit(-1);
				}
				break;
			case 1:	
				break;		
			default:
				break;
		}	
	}
	
	pthread_exit(NULL);
}

void *criaThread(void *threadArg){
	
	struct thread_data *my_data = (struct thread_data*) threadArg;
	
	printf("\nOlá! Sou a thread %d.\n", my_data->thread_id);
	free(my_data);
	
	pthread_exit(NULL);
}
