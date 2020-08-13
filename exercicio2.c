/*
OMP - Atividade Individual Avaliativa; Questão 1
*/

#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

void gradesfunc(int graph[][6], int tid, int nthreads);

int main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	int graph[6][6] = {{0, 1, 0, 0, 2, 0}, {1, 0, 3, 0, 2, 0}, {0, 3, 0, 6, 0, 0}, {0, 0, 6, 0, 4, 3}, {2, 2, 0, 4, 0, 0}, {0, 0, 0, 3, 0, 0}};
	int grades[6];
	int nthreads, tid, value = 0;
	
	#pragma omp parallel shared(graph, grades, nthreads, tid)
	{
		tid = omp_get_thread_num();
		nthreads = omp_get_num_threads();
		
		gradesfunc(graph, tid, nthreads);
	}
}

void gradesfunc(int graph[][6], int tid, int nthreads){
	
	int grades[6];
	int grade = 0, i, g = 0;
	
	switch (tid){
		case 0:
			for(i = 0; i < nthreads; i++){
				if(graph[tid][i] > 0){
					grade++;
				}
			}	
			grades[tid] = grade;
		case 1:
			for(i = 0; i < nthreads; i++){
				
				if(graph[tid][i] >= 1){
					
					grade++;
				}
			}
			grades[tid] = grade;
		case 2:
			for(i = 0; i < nthreads; i++){
				
				if(graph[tid][i] >= 1){
					
					grade++;
				}
			}
			grades[tid] = grade;
		case 3:
			for(i = 0; i < nthreads; i++){
				
				if(graph[tid][i] >= 1){
					
					grade++;
				}
			}
			grades[tid] = grade;
		case 4:
			for(i = 0; i < nthreads; i++){
				
				if(graph[tid][i] >= 1){
					
					grade++;
				}
			}
			grades[tid] = grade;
		case 5:
			for(i = 0; i < nthreads; i++){
				
				if(graph[tid][i] >= 1){
					
					grade++;
				}
			}
			grades[tid] = grade;
	}
	g = 0;
	for(i = 0; i < 6; i ++){
		
		if(grades[i] > g){
			
			g = grades[i];
		}
	}
	
	printf("\nO maior grau é %d", g);
	for(i = 0; i < 6; i++){
			
		printf("\nO grau do vértice %d é %d", i, grades[i]);		
	}
}
