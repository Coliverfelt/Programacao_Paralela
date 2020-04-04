#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<locale.h>
#include<stdint.h>

#define NUM_PROC 1
#define NUM_THREAD 3

void *cria1Thread(void *tid_ant);
void *cria3Threads(void *tid_ant);

int main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	
	pthread_t proc[NUM_PROC];
	int returnCode;
	intptr_t id;
	
	for(id = 1; id < 2; id++){
		
		printf("\nOlá! estou criando o %d º processso...", id);
		returnCode = pthread_create(&proc[id], NULL, cria1Thread, (void *)id);
		
		if(returnCode){
			
			printf("\nERRO! returnCode da pthread_create foi %d.", returnCode);
			exit(-1);
		}
	}

	pthread_exit(NULL);	
}

void *cria1Thread(void *tid_ant){
	
	pthread_t thread[NUM_THREAD - 2];
	int returnCode;
	intptr_t tid = (intptr_t) tid_ant;
	intptr_t id;
	
	for(id = 1; id <= tid; id++){
		
		if((tid == 2) or (tid == 5) or (tid == 6)){
			
			pthread_exit(NULL);
		}else if((tid == 3) or (tid == 4)){
			
			if(tid == 3){
				
				id = 5;
			}else{
				
				id = 6;
			}
			
			printf("\nEstamos criando a %d ª thread, filha do processo %d...", id, tid);
			returnCode = pthread_create(&thread[id], NULL, cria1Thread, (void *)id);
			
			if(returnCode){
				
				printf("\nERRO! returnCode da pthread_create foi %d.", returnCode);
				exit(-1);
			}
		}else{
			
			printf("\nEstamos criando a %ld ª thread, filha do processo %ld...", id, tid);
			returnCode = pthread_create(&thread[id], NULL, cria3Threads, (void *)id);
			
			if(returnCode){
				
				printf("\nERRO! returnCode da pthread_create foi %d.", returnCode);
				exit(-1);
			}	
		}
	}

	pthread_exit(NULL);
}

void *cria3Threads(void *tid_ant){
	
	pthread_t threads[NUM_THREAD];
	int returnCode;
	intptr_t tid = (intptr_t) tid_ant;
	intptr_t id = 2;
	
	for(id = 2; id <= (NUM_THREAD + 1); id++){
		
		printf("\nEstamos criando a %d ª thread, filha da thread %d...", id, tid);
		returnCode = pthread_create(&threads[id], NULL, cria1Thread, (void *)id);
		
		if(returnCode){
			
			printf("\nERRO! returnCode da pthread_create foi %d.", returnCode);
			exit(-1);
		}
	}
	
	pthread_exit(NULL);
}
