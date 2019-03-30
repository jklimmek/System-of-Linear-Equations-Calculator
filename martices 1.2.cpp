// Macierze 1.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "func.h"
#include "Vector.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define CNTRL	// wydruki kontrolne

void readData(FILE* fin, double** pMatrix, double* bTab, int nDim);

//void fillTab(double*** pTab, int nSize);


int main(int argc, char** argv)
{
	if (argc != 2) {
		printf("niepoprawna ilosc parametrow\n");
		return 0;
	}

	int nSize;
	FILE* fin;
	if ((fin = fopen(argv[1], "r")) == NULL){
		printf("nie udalo sie otworzyc pliku\n");
		return 0;
	}
	fscanf(fin, "%d", &nSize);
	double** pTab = NULL;		// matrix NxN
	double* bTab = NULL;		// vector N

	if (!createMatrix(&pTab, nSize) || !createVec(&bTab, nSize))
		return 0;

			readData(fin, pTab, bTab, nSize);

			double det = determinant(pTab, nSize);

			double** inv = NULL;
			if (!createMatrix(&inv, nSize))
				return 0;

			inverseMatrix(inv, pTab, nSize, det);

			double* pRes = NULL;
			if (!createVec(&pRes, nSize))
				return 0;
			layoutEquation(inv, bTab, pRes, nSize);
#ifdef CNTRL
			printf("current matrix:\n");
			printMatrix(pTab, nSize);
			printf("\ncurrent vector:\n");
			printVec(bTab, nSize);
			printf("\n\n");
			printf("\ninversed matrix:\n");
			printMatrix(inv, nSize);
			printf("\n\n");
			printf("\nsolution:\n");
			printVec(pRes, nSize);
			printf("\n\n");
#endif // CNTRL

			deleteMatrix(&pTab, nSize);
			deleteMatrix(&inv, nSize);
			deleteVec(&bTab, nSize);
			deleteVec(&pRes, nSize);
	return 0;
}

/*void fillTab(double*** pTab, int nSize) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < nSize; i++) {
		for (int j = 0; j < nSize; j++) {
			(*pTab)[i][j] = rand() % 10;
		}
	}
}*/

void readData(FILE* fin, double** pMatrix, double* bTab, int nDim) {

	for (int i = 0; i < nDim; i++){
		double* p = *pMatrix++;
		for (int j = 0; j < nDim; j++)
			fscanf(fin, "%lf", p++);
		fscanf(fin, "%lf", bTab++);
	}
}