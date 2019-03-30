#include "func.h"
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <iostream>

using namespace std;

void transposeMatrix(double** pTab, int nDim);
void complMatrix(double** ptabD, double** pTab, int nDim);						//macierz dopelnien 
void complement(double** pTabO, double** pTabT, int nRow, int nCol, int nDim);	//macierz 1<

int createMatrix(double*** pTab, int nSize) {
	*pTab = (double**)calloc(nSize, sizeof(int*));
	if (!pTab) {
		perror("nie udalo sie zaalokowac pamieci\n");
		return 0;
	}
	double** p = *pTab;
	for (int i = 0; i < nSize; i++, p++) {
		*p = (double*)calloc(nSize, sizeof(double));
		if (!p) {
			perror("nie udalo sie zaalokowac pamieci\n");
			return 0;
		}
	}
	return 1;
}

void deleteMatrix(double*** pTab, int nSize) {
	for (int i = 0; i < nSize; i++)
		free((*pTab)[i]);
	free(*pTab);
	*pTab = NULL;
}

void inverseMatrix(double** pInv, double** pTab, int nSize, double det) {
	if (det == 0) {
		printf("nie mozna policzyc macierzy odwrotnej: wyznacznik = 0\n");
		return;
	}
	for (int i = 0; i < nSize; i++) {
		double* ptr1 = *pInv++;
		double* ptr2 = *pTab++;
		for (int j = 0; j < nSize; j++) {
			*ptr1++ = (*ptr2++) / det;
		}
	}
}

double determinant(double** pTab, int nSize) {
	double det = 0;
	double power = 1;
	double** a = NULL;
	double* ptr = *pTab;

	if (!createMatrix(&a, nSize - 1)) {
		perror("nie udalo sie zaalokowac pamieci\n");
		exit(-1);
	}
	

	if (nSize == 1)
		return **pTab;
	if (nSize == 2)
		return **pTab * pTab[1][1] - pTab[0][1] * pTab[1][0];
	
		for (int j1 = 0; j1 < nSize; j1++) {
			complement(a, pTab, 0, j1, nSize);
			det +=  power * (*ptr++) * determinant(a, nSize - 1);
			power = -power;
		}

	return det;
}

void layoutEquation(double** pInv, double* pB, double* pRes, int nSize) {
	double** pTmp = pInv;
	for (int i = 0; i < nSize; i++, pRes++) {
		double *p = pB;
		double *t = *pTmp;
		for (int j = 0; j < nSize; j++) {
			*pRes += (*t++) * (*p++);
		}
		*pTmp++;
	}
}

void printMatrix(double** pTab, int nSize) {
	for (int i = 0; i < nSize; i++) {
		double* ptr = *pTab++;
		for (int j = 0; j < nSize; j++)
			printf("%.3lf ", *ptr++);
		printf("\n");
	}
}

void transposeMatrix(double** pTab, int nDim) {
	for (int i = 0; i < nDim - 1; i++) {
		double* ptr = *(pTab + i) + i + 1;
		for (int j = i + 1; j < nDim; j++) {
			double temp = *ptr;
			*ptr++ = pTab[j][i];
			pTab[j][i] = temp;
		}
	}
}

void complMatrix(double** pTabD, double** pTab, int nDim) {

	double** pTmp = NULL;
	createMatrix(&pTmp, nDim - 1);

	for (int i = 0; i < nDim; i++){
		double* ptr = *pTabD;
		int power = (i % 2) ? -1 : 1;
		for (int j = 0; j < nDim; j++) {
			complement(pTmp, pTab, i, j, nDim);
			
			*ptr++ = power * determinant(pTmp, nDim - 1);
			power = -power;
		}
	}
}

void complement(double** pTabO, double** pTabT, int nRow, int nCol, int nDim) {

	for (int i = 0; i < nDim; i++) {
		double* pO = *pTabO;
		double* pT = *pTabT++;
		if (i == nRow)
			continue;
		for (int j = 0; j < nDim; j++, pT++) {
			if (j == nCol)
				continue;
			*pO++ = *pT;
			
		}
		pTabO++;
	}
}
