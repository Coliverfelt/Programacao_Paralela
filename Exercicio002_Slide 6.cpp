/*
2.Crie um programa em C com duas threads. Uma deve 
invocar uma rotina que calcula o somatório dos valores 
contidos em um vetor, enquanto a outra deve encontrar o 
maior elemento do mesmo vetor.
*/

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

#define NUM_THREADS 2
#define TAM_VETOR 6

struct thread_data{
	int thread_id;
	int vetor[TAM_VETOR] = {8, 0, 3, 10, 7, 9};
};

struct thread_data thread_data_array[NUM_THREADS];

void *soma(void *threadArg);
void *maior(void *threadArg);

int main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	
	pthread_t threads[NUM_THREADS];
	long id;
	int returnCode;
	
	for(id = 0; id < NUM_THREADS; id++){
		
		printf("\nCriando Thread[%ld]...", id);
		if (id == 0){
				
			thread_data_array[id].thread_id = id;
			returnCode = pthread_create(&threads[id], NULL, soma, (void *) &thread_data_array[id]);
		}else{
			
			thread_data_array[id].thread_id = id;
			returnCode = pthread_create(&threads[id], NULL, maior, (void *) &thread_data_array[id]);		
		}
		
		if(returnCode){
			
			printf("\nERROR! Retorno do código da pthread_create() is %d.\n", returnCode);
			exit(-1);
		}
	}
	
	pthread_exit(NULL);
}

void *soma(void *threadArg){
	
	struct thread_data *my_data;
	my_data = (struct thread_data *) threadArg;
	int soma = 0;
	
	for(int i = 0; i < TAM_VETOR; i++){
		
		soma += my_data -> vetor[i];
	}
	
	printf("\nA soma do vetor é %d.", soma);
	
	pthread_exit(NULL);
}

void *maior(void *threadArg){
	
	struct thread_data *my_data;
	my_data = (struct thread_data *) threadArg;
	int maior = my_data -> vetor[0];
	
	for(int i = 0; i < TAM_VETOR; i++){
		
		if(my_data -> vetor[i] > maior){
			
			maior = my_data -> vetor[i];
		}
	}
	
	printf("\nO maior valor do vetor é %d.", maior);
	
	pthread_exit(NULL);
}
