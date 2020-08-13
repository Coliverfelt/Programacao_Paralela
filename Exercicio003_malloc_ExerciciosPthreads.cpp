/*
3)Altere o programa anterior de modo que cada thread criada simule um serviço no qual é solicitado
um valor para o usuário antes de continuar.
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdint.h>
#include<locale.h>

#define NUM_THREAD 1

int valor = NULL;

struct thread_data{
	
	int thread_id;
};

void *criaThread(void *threadArg);

int main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	int threadcount = 0;

	while(1){
		
		if((threadcount == 0) or (valor != NULL)){	
			
			//printf("\nThreadCount: %d", threadcount);
			//printf("\nValor: %d\n", valor);
			
			printf("\nVocê deseja criar uma thread?");
			printf("\n0 - SIM");
			printf("\n1 - NÃO");
			printf("\n2 - SAIR");
			printf("\n");
		
			int user = 0;
			scanf("%d", &user);
			
			struct thread_data *threads_data;
			pthread_t *thread;
			int rc;
			
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
					
					valor = NULL;
					
					break;
				case 1:	
				
					break;	
				case 2:
					
					pthread_exit(NULL);
					
					break;	
				default:
					
					printf("\nERRO!");
					printf("\nFavor inserir um número de 0 a 2.");
					
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
	
	free(my_data);
	
	pthread_exit(NULL);
}
