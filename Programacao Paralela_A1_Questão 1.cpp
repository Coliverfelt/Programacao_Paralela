#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<stdint.h>
#include<windows.h>
#include<pthread.h>

#define QTD_VERTICE 6

int matriz[QTD_VERTICE][QTD_VERTICE];
int arestas[QTD_VERTICE], peso[QTD_VERTICE], vmg[QTD_VERTICE];
int maiorgrau = 0;
pthread_mutex_t mutexcomp;

void *maiorGrau(void* id);

int main(int argc, char *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	
	for(int i = 0; i < QTD_VERTICE; i++){
		
		if(i == 0){
			
			matriz[i][0] = 0;
			matriz[i][1] = 1;
			matriz[i][2] = 0;
			matriz[i][3] = 0;
			matriz[i][4] = 2;
			matriz[i][5] = 0;
		}else if(i == 1){
			
			matriz[i][0] = 1;
			matriz[i][1] = 0;
			matriz[i][2] = 3;
			matriz[i][3] = 0;
			matriz[i][4] = 2;
			matriz[i][5] = 0;
		}else if(i == 2){
			
			matriz[i][0] = 0;
			matriz[i][1] = 3;
			matriz[i][2] = 0;
			matriz[i][3] = 6;
			matriz[i][4] = 0;
			matriz[i][5] = 0;
		}else if(i == 3){
			
			matriz[i][0] = 0;
			matriz[i][1] = 0;
			matriz[i][2] = 6;
			matriz[i][3] = 0;
			matriz[i][4] = 4;
			matriz[i][5] = 3;
		}else if(i == 4){
			
			matriz[i][0] = 2;
			matriz[i][1] = 2;
			matriz[i][2] = 0;
			matriz[i][3] = 4;
			matriz[i][4] = 0;
			matriz[i][5] = 0;
		}else if(i == 5){
			
			matriz[i][0] = 0;
			matriz[i][1] = 0;
			matriz[i][2] = 0;
			matriz[i][3] = 3;
			matriz[i][4] = 0;
			matriz[i][5] = 0;
		}
	}

	pthread_t threads[QTD_VERTICE];
	int rc;
	for(intptr_t id = 0; id < QTD_VERTICE; id++){
		
		printf("\nCriando a thread %d...", id);
		rc = pthread_create(&threads[id], NULL, maiorGrau, (void *) id);
		
		if(rc){
			
			printf("\nERRO! pthread_create retornou %d.", rc);
			
			exit(-1);
		}
	}
	
	//Sleep(50);
	
	printf("\nO(s) vértice(s) de maior grau é/são: ");
	for(int j = 0; j < QTD_VERTICE; j++){
		if(vmg[j] > 0){
			
			if(vmg[j] == 0){
				
				printf("\tA; ");
			}else if(vmg[j] == 1){
				
				printf("\tB; ");
			}else if(vmg[j] == 2){
				
				printf("\tC; ");
			}else if(vmg[j] == 3){
				
				printf("\tD; ");
			}else if(vmg[j] == 4){
				
				printf("\tE; ");
			}else if(vmg[j] == 5){
				
				printf("\tF; ");
			}
		}
	}
	
	printf("\nO(s) vértice(s) com maior peso é/são: ");
	int maiorpeso = 0;
	for(int j = 0; j < QTD_VERTICE; j++){
		if(peso[j] > maiorpeso){
			
			maiorpeso = peso[j];
			
			if(peso[j] == 0){
				
				printf("\tA; ");
			}else if(peso[j] == 1){
				
				printf("\tB; ");
			}else if(peso[j] == 2){
				
				printf("\tC; ");
			}else if(peso[j] == 3){
				
				printf("\tD; ");
			}else if(peso[j] == 4){
				
				printf("\tE; ");
			}else if(peso[j] == 5){
				
				printf("\tF; ");
			}
		}
	}	
	pthread_exit(NULL);
}

void *maiorGrau(void* id){
	
	intptr_t no_id = (intptr_t) id;
	int count, pes = 0;
	
	printf("\nEu sou a thread %d.", no_id);
	
	for(int i = 0; i < QTD_VERTICE; i++){
	
		if(matriz[no_id][i] != 0){
		
			count += 1;
			pes += matriz[no_id][i];
		}		
	}
	
	pthread_mutex_lock (&mutexcomp);
	arestas[no_id] = count;
	peso[no_id] = pes;
	pthread_mutex_unlock (&mutexcomp);

	if(arestas[no_id] >= maiorgrau){
		
		maiorgrau = arestas[no_id];
		vmg[no_id] = no_id;
	}
	
	pthread_exit(NULL);
}
