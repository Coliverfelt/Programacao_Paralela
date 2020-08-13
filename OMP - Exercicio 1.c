/*
OMP - Exerc�cio 1
*/

#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

int main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	
	int nthreads, tid, value;
	
	/* Divide em um conjunto de threads, cada uma com suas pr�prias vari�veis. */
	#pragma omp parallel shared(value) private(nthreads, tid)
	{
		
		/* Obt�m o ID da thread. */
		tid = omp_get_thread_num(); // Fun��o que retorna o ID da thread.
		printf("\nHello, I'm thread %d.", tid);
		
		//system("stress -c 1");
		
		if(tid == 0){
			
			nthreads = omp_get_num_threads(); // Fun��o que retorna a quantidade de threads.
			printf("\nNumber of threads: %d.", nthreads);
		}
	} /* Aqui, todas as threads se juntam ao processo principal e encerram. */
}
