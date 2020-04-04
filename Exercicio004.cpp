#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<stdint.h>

#define NUM_THREAD 1

struct thread_data{
	
	int thread_id;
};

struct thread_data thread_array[NUM_THREAD];

void *criathread(void *threadArg);

int main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	pthread_t threads[NUM_THREAD];
	
	int returnCode;
	intptr_t id;
	
	int user;
	int count = 0;
	
	do{
		
		printf("\nVoc� deseja criar uma thread? [0-SIM / 1-N�O / 2-SAIR]\n");
		scanf("%d", &user);
		
		while(user == 1){
			
			printf("\nVoc� deseja criar uma thread? [0-SIM / 1-N�O / 2-SAIR]\n");
			scanf("%d", &user);
		}
		
		while((user != 0) and (user != 1) and (user != 2)){
			
			printf("\nERRO! N�mero inv�lido...");
			
			printf("\nVoc� deseja criar uma thread? [0-SIM / 1-N�O / 2-SAIR]\n");
			scanf("%d", &user);
		}
		
		if(user == 0){
			
			for(id = 1; id <= NUM_THREAD; id++){
				
				printf("\nEstamos criando a %d� thread...", id + count);
				thread_array[id].thread_id = id + count;
				returnCode = pthread_create(&threads[id], NULL, criathread, (void *) &thread_array[id]);
				
				if(returnCode){
					
					printf("\nERRO! returnCode de pthread_create � %d.", returnCode );
				}else{
					
					count += 1;
				}	
			}
		}		
	}while(user != 2);
	
	pthread_exit(NULL);
}

void *criathread(void *threadArg){
	
	struct thread_data *my_data;
	my_data = (struct thread_data*) threadArg;
	
	printf("\nOl�! Sou a thread %d.\n", my_data->thread_id);
	
}
