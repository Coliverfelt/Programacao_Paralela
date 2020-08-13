#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void who_am_i (int id) {
	if (id == 0) {
		printf ("I'm the master!!!!\n");
	}
	else {
		printf ("I am process %d\n", id);
	}
}

void show_elem (int *v, int id) {
	printf ("I am thread %d and my value in the array is %d\n", id, v[id]);
}


int main (int argc, char *argv[]) {
	int nthreads, tid, value = 0, vet[8] = {3, 2, 7, 1, 0, 9, 4, 5};

	//Definição da diretiva do OpenMP
	//Diretiva OpenMP que determina o processamento paralelo padrão entre todas as threads criadas, com variável compartilhada value e as variáveis privadas nthreads e tid 
	#pragma omp parallel shared (value, vet) private (nthreads, tid) num_threads(4)
	{
		tid = omp_get_thread_num ();
		// printf ("Hello from thread %d\n", tid);
		//who_am_i (tid);
		// show_elem (vet, tid);
		if (tid != 0) {
			value = tid; // troca do valor da variável compartilhada
			printf ("Process %d changed value to %d\n", tid, value);
		}

		if (tid == 0 ) {
			nthreads = omp_get_num_threads ();
			printf ("I am thread %d and we have %d threads\n", tid, nthreads);
			value = 10; // troca do valor da variável compartilhada
			printf ("Process %d changed value to %d\n", tid, value);
		}
	}
	// Fim da diretiva pragma e do processamento paralelo

	return 0;
}









