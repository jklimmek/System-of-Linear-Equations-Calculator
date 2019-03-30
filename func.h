#ifndef FUNC
#define FUNC

// matrix.h
int createMatrix(double*** pTab, int nSize);
void deleteMatrix(double*** pTab, int nSize);
void inverseMatrix(double** pInv, double** pTab, int nSize, double det);
double determinant(double** pTab, int nSize);
void layoutEquation(double** pInv, double* pB, double* pRes, int nSize);
void printMatrix(double** pTab, int nSize);

#endif // !FUNC

