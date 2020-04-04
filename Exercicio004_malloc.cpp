#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdint.h>
#include<locale.h>

#define NUM_THREAD

struct thread_data{
	
	int thread_id;
};

int main(int argc, char *argv){
	
	setlocale(LC_ALL, "Portuguese");
	int threadcount = 0;
	
	while(1){
		
		printf("\nVocê deseja criar uma thread?");
		printf("\n0 - SIM");
		printf("\n1 - NÃO");
		printf("\n2 - SAIR");
		
		int user;
		scanf("%d", &user);
		
		switch(user){
			
			case 0:
				
				threadcount++;
				
				int rc;
				pthread_t *thread = malloc(NUM_THREAD * sizeof(pthread_t));
				
				printf("\nCriando thread %d...", threadcount);
				
				
				
				if(rc){
					
					printf("\nERRO! Return Code da pthread_create é %d.", rc);
					exit(-1);
				}
			
			case 1:
				
				break;
				
			default:
				
				break;
		}	
	}
}

void *criathread(void *threadArg){
	
	
}
