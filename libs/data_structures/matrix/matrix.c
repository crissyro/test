#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);

    return (matrix){values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);

    return ms;
}

void freeMemMatrix(matrix *m) {
    if (m == NULL) {
        return;
    }

    for (int i = 0; i < m->nRows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    if (ms == NULL) {
        return;
    }

    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }

    free(ms);
}