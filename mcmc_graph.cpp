#include <iostream>
#include <cstring>

#define MAX 4294967295
using namespace std;

unsigned long long int** gen_initial_graph(int v, int e) {
	unsigned long long int **graph = (unsigned long long int**) malloc(v * sizeof(unsigned long long int *));
	for(int i = 0; i < v; i++) {
		*(graph + i) = (unsigned long long int *) malloc(v * sizeof(unsigned long long int));
		for(int j = 0; j < v; j++) {
			*(*(graph + i) + j) = 0;
		}
	}


	for(int i = 0; i < e; i++) {
		*(*(graph + i%v) + (i+1)%v) += 1;
		*(*(graph + (i+1)%v) + i%v) += 1;
	}

	return graph;
}

unsigned long long int** floyd_warshall(unsigned long long int **graph, int size) {

	unsigned long long int **dist = (unsigned long long int **) malloc(size * sizeof(unsigned long long int *));
	for(int i = 0; i < size; i++) {
		*(dist + i) = (unsigned long long int *) malloc(size * sizeof(unsigned long long int));
		for(int j = 0; j < size; j++) {
			
			if( i == j) {
				*(*(dist + i) + j) = 0;
			}
			else if (*(*(graph + i) + j) > 0) {
				*(*(dist + i) + j) = 1;
			}
			else {
				*(*(dist + i) + j) = MAX;
			} 
			
		}
	}

	for(int k = 0; k < size; k++) {
		for(int i = 0; i < size; i++) {
			for(int j = 0; j < size; j++) {
				*(*(dist + i) + j) = *(*(dist + i) + j) < *(*(dist + i) + k) + *(*(dist + k) + j) ? *(*(dist + i) + j) : *(*(dist + i) + k) + *(*(dist + k) + j);
			}
		}
	}

	return dist;

}

unsigned long long int sum_edges(unsigned long long int **graph, int size) {
	unsigned long long int sum = 0;

	unsigned long long **dist = floyd_warshall(graph, size);

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(*(*(dist + i) + j) != MAX) {
	        		sum += *(*(dist + i) + j);
			}
	       	}	
	}

	return sum;
}

long double mean_distance(unsigned long long int **graph, int size) {
	return (2*sum_edges(graph, size))/(size*(size - 1));
}

long double graph_efficiency(unsigned long long int **graph, int size) {
	
	unsigned long long int **dist = floyd_warshall(graph, size);
	
	long double **ef_matrix = (long double **) malloc(size * sizeof(long double *));
	
	for(int i = 0; i < size; i++) {
		*(ef_matrix + i) = (long double *) malloc(size * sizeof(long double));
		
		for(int j = 0; j < size; j++) {

			if(*(*(dist + i) + j) > 0 && *(*(dist + i) + j) != MAX) {
				*(*(ef_matrix + i) + j) = 1/(long double) *(*(dist + i) + j);
			}
			else {
				*(*(ef_matrix + i) + j) = 0;
			}

		}
	}

	long double sum = 0.0;

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			sum +=  *(*(ef_matrix + i) + j);
		}
		
	}

	return sum * (1/( (long double) size*(size - 1)));
}

int main() {
	int vertices = 9;
	int edges = 6;
	unsigned long long **graph = gen_initial_graph(vertices, edges);
	
	printf("%lld\n", sum_edges(graph, vertices));
	printf("%LF\n", mean_distance(graph, vertices));
	printf("%LF\n", graph_efficiency(graph, vertices));
	

}
