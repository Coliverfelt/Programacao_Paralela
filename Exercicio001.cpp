/*
1.Criar um programa em C com 4 threads no qual cada uma
delas multiplica o seu próprio thread_id por um valor
randômico entre 1 e 10, gerado pela função principal. Após
multiplicar, cada thread deve exibir o valor randômico e o
produto.
*/

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define NUM_THREADS 4

struct thread_data{
	
	int thread_id;
	int rand;
};

struct thread_data thread_data_array[NUM_THREADS];

void *multiplicaId(void *threadArg);

int main(int argc, char *argv[]){
	
	pthread_t threads[NUM_THREADS];
	long id;
	int returnCode;
	
	for(id = 1; id <= NUM_THREADS; id++){
		
		int vRandom = rand() % (10 + 1 - 0) + 0;
		
		printf("In main: creating thread %ld \n", id);
		thread_data_array[id].thread_id = id;
		thread_data_array[id].rand = vRandom;
		returnCode = pthread_create(&threads[id], NULL, multiplicaId, (void *) &thread_data_array[id]);
		
		if(returnCode){
			
			printf("ERROR; return code from pthread_create() is %d \n", returnCode);
			exit(-1);
		}
	}
	
	pthread_exit(NULL);
}

void *multiplicaId(void *threadArg){

	struct thread_data *my_data;
		
	my_data = (struct thread_data *) threadArg;
	
	printf("\nHello! It's me, thread #%d! And my random is %d.\n", my_data->thread_id * my_data->rand, my_data->rand);
	pthread_exit(NULL);
}
