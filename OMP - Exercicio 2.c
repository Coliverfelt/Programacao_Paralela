/*
OMP - Atividade Individual Avaliativa; Questão 1
*/

#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

int grades[6];

void gradesfunc(int graph[][6], int tid, int nthreads);

int main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	int graph[6][6] = {{0, 1, 0, 0, 2, 0}, {1, 0, 3, 0, 2, 0}, {0, 3, 0, 6, 0, 0}, {0, 0, 6, 0, 4, 3}, {2, 2, 0, 4, 0, 0}, {0, 0, 0, 3, 0, 0}};
	int nthreads, tid, value = 0;
	
	#pragma omp parallel shared(graph, grades, nthreads, tid) num_threads(6)
	{
		tid = omp_get_thread_num();
		nthreads = omp_get_num_threads();
		
		gradesfunc(graph, tid, nthreads);
	}
	
	int g = 0, i;
	for(i = 0; i < 6; i ++){
		
		if(grades[i] > g){
			
			g = grades[i];
		}
	}
	
	printf("\nO maior grau é %d", g);
	for(i = 0; i < 6; i++){
		
		printf("\nO grau do vértice %d é %d.", i, grades[i]);	
	}
}

void gradesfunc(int graph[][6], int tid, int nthreads){

	int grade = 0, i; printf("\nAQUI");
	if(tid == 0){
		
		for(i = 0; i < 6; i++){
			if(graph[tid][i] > 0){
				grade++;
			}
		}
		grades[tid] = grade;
		grade = 0;
	}
	if(tid == 1){
		
		for(i = 0; i < 6; i++){
				
			if(graph[tid][i] > 0){
				
				grade++;
			}
		}
		grades[tid] = grade;
		grade = 0;
	}
	if(tid == 2){
		
		for(i = 0; i < 6; i++){
				
			if(graph[tid][i] > 0){
				
				grade++;
			}
		}
		grades[tid] = grade;
		grade = 0;
	}
	if(tid == 3){
		
		for(i = 0; i < 6; i++){
				
			if(graph[tid][i] > 0){
				
				grade++;
			}
		}
		grades[tid] = grade;
		grade = 0;
	}
	if(tid == 4){
		
		for(i = 0; i < 6; i++){
				
			if(graph[tid][i] > 0){
				printf("\nGraph[%d][%d] = %d", tid, i, graph[tid][i]);
				grade++;
			}
		}
		grades[tid] = grade;
		grade = 0;
	}
	if(tid == 5){
		
		for(i = 0; i < 6; i++){
				
			if(graph[tid][i] > 0){
				
				grade++;
			}
		}
		grades[tid] = grade;
		grade = 0;
	}
}
