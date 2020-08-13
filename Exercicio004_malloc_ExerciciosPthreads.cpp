/*
4)Altere o programa anterior de maneira a permitir ao usuário escolher qual serviço ele deseja iniciar
por meio de uma thread.
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdint.h>
#include<locale.h>

#define NUM_THREAD 1

int valor = 1;
int user = 999;
int block = 0;

struct thread_data{
	
	int thread_id;
};

void *criaThread(void *threadArg);

int main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	int threadcount = 0;

	while(1){
		
		if(threadcount == 0){

			printf("\nVocê deseja criar uma thread?");
			printf("\n0 - SIM");
			printf("\n1 - NÃO");
			printf("\n2 - SAIR");
			printf("\n");
			
			scanf("%d", &user);
		}
		
		if((user == 999) and (block == 1)){

			printf("\nERRO!");
			printf("\nFavor inserir um número de 0 a 2.");
					
			printf("\nVocê deseja criar uma thread?");
			printf("\n0 - SIM");
			printf("\n1 - NÃO");
			printf("\n2 - SAIR");
			printf("\n");
			
			scanf("%d", &user);
		}
		
		if((user != 999) and (valor != NULL)){	
		
			struct thread_data *threads_data;
			pthread_t *thread;
			int rc;
			
			switch(user){	
				case 0:
					
					user = 999;
					
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
					
					valor = NULL;
					block = 0;
					break;
				case 1:	
					
					printf("\nVocê deseja criar uma thread?");
					printf("\n0 - SIM");
					printf("\n1 - NÃO");
					printf("\n2 - SAIR");
					printf("\n");
		
					scanf("%d", &user);
					
					break;	
				case 2:
					
					pthread_exit(NULL);
					
					break;	
				default:
					
					printf("\nERRO!");
					printf("\nFavor inserir um número de 0 a 2.");
					
					printf("\nVocê deseja criar uma thread?");
					printf("\n0 - SIM");
					printf("\n1 - NÃO");
					printf("\n2 - SAIR");
					printf("\n");
		
					scanf("%d", &user);
					break;
			}
		}	
	}
}

void *criaThread(void *threadArg){
	
	struct thread_data *my_data = (struct thread_data*) threadArg;
	
	printf("\nOlá! Sou a thread %d.\n", my_data->thread_id);
	
	printf("\nDigite um valor para continuar: ");
	scanf("%d", &valor);
	
	printf("\nVocê deseja criar uma thread?");
	printf("\n0 - SIM");
	printf("\n1 - NÃO");
	printf("\n2 - SAIR");
	printf("\n");

	scanf("%d", &user);
	
	block = 1;
	free(my_data);
	
	pthread_exit(NULL);
}
