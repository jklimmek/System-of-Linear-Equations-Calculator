#include "Vector.h"
#include <memory.h>
#include <cstdlib>
#include <iostream>

int createVec(double** vec, int nSize) {
	*vec = (double*)calloc(nSize, sizeof(double));
	return (vec) ? 1 : printf("nie udalo sie zaalokowac pamieci\n"); 0;
}

void printVec(double* vec, int nSize) {
	double* p = vec;
	for (int i = 0; i < nSize; i++){
		printf("%.3lf ", *p++);
	}
}

void deleteVec(double** vec, int nSize) {
	free(*vec);
	*vec = NULL;
}