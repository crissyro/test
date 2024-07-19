#include "matrix.h"


matrix getMemMatrix(const int nRows, const int nCols) {
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

void inputMatrix(matrix *m) {
    printf("Введите количество строк матрицы: ");
    scanf("%d", &m->nRows);

    printf("Введите количество столбцов матрицы: ");
    scanf("%d", &m->nCols);

    m->data = (int*)malloc(m->nRows * m->nCols * sizeof(int));

    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < m->nRows; i++)
        for (int j = 0; j < m->nCols; j++) {
            printf("Элемент [%d][%d]: ", i, j);
            scanf("%d", &m->data[i * m->nCols + j]);
        }

}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(&ms[i]);
    }
}

void outputMatrix(matrix m) {
    printf("Матрица %dx%d:\n", m.nRows, m.nCols);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d ", m.data[i * m.nCols + j]);
        }
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        printf("Матрица %d:\n", i + 1);
        outputMatrix(ms[i]);
        printf("\n");
    }
}


void swapRows(matrix m, int i1, int i2) {
    assert(i1 >= 0 && i1 < m.nRows);
    assert(i2 >= 0 && i2 < m.nRows);

    if (i1 == i2) {
        return;
    }

    for (int j = 0; j < m.nCols; j++) {
        int *temp = m.data[i1 * m.nCols + j];
        m.data[i1 * m.nCols + j] = m.data[i2 * m.nCols + j];
        m.data[i2 * m.nCols + j] = temp;
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)) {
    int *criteriaValues = (int*)malloc(m.nRows * sizeof(int));

    for (int i = 0; i < m.nRows; i++) {
        int rowSum = 0;
        for (int j = 0; j < m.nCols; j++) {
            rowSum += *m.data[i * m.nCols + j];
        }
        criteriaValues[i] = criteria(&m.data[i * m.nCols], m.nCols);
    }

    for (int i = 1; i < m.nRows; i++) {
        int key = criteriaValues[i];
        int *keyRow = m.data[i * m.nCols];
        int j = i - 1;

        while (j >= 0 && criteriaValues[j] > key) {
            criteriaValues[j + 1] = criteriaValues[j];
            for (int k = 0; k < m.nCols; k++) {
                m.data[(j + 1) * m.nCols + k] = m.data[j * m.nCols + k];
            }
            j--;
        }

        criteriaValues[j + 1] = key;
        for (int k = 0; k < m.nCols; k++) {
            m.data[(j + 1) * m.nCols + k] = keyRow;
        }
    }

    free(criteriaValues);
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)) {
    for (int i = 0; i < m.nCols; i++) {
        for (int j = i + 1; j < m.nCols; j++) {
            int sum1 = 0;
            int sum2 = 0;

            for (int k = 0; k < m.nRows; k++) {
                sum1 += *m.data[k * m.nCols + i];
                sum2 += *m.data[k * m.nCols + j];
            }

            if (criteria(&sum2, 1) < criteria(&sum1, 1)) {
                for (int k = 0; k < m.nRows; k++) {
                    int *temp = m.data[k * m.nCols + i];
                    m.data[k * m.nCols + i] = m.data[k * m.nCols + j];
                    m.data[k * m.nCols + j] = temp;
                }
            }
        }
    }
}

bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    return memcmp(m1->data, m2->data, m1->nRows * m1->nCols * sizeof(int)) == 0;
}

bool isEMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false;
    }

    // Проверяем элементы на соответствие единичной матрице
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (i == j && m->data[i * m->nCols + j] != 1) {
                return false;
            } else if (i != j && m->data[i * m->nCols + j] != 0) {
                return false;
            }
        }
    }

    return true;
}

bool isSymmetricMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            if (m->data[i * m->nCols + j] != m->data[j * m->nCols + i]) {
                return false;
            }
        }
    }

    return true;
}

void transposeSquareMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        printf("Матрица не квадратная, транспонирование невозможно.\n");
        return;
    }

    int *temp;
    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            // Меняем местами элементы относительно главной диагонали
            temp = m->data[i * m->nCols + j];
            m->data[i * m->nCols + j] = m->data[j * m->nCols + i];
            m->data[j * m->nCols + i] = temp;
        }
    }
}

void transposeMatrix(matrix *m) {
    int temp;
    int *transposedMatrix = (int *)malloc(m->nRows * m->nCols * sizeof(int));

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            transposedMatrix[j * m->nRows + i] = *m->data[i * m->nCols + j];
        }
    }

    free(m->data);

    m->data = transposedMatrix;

    int tempRows = m->nRows;
    m->nRows = m->nCols;
    m->nCols = tempRows;
}

position getMinValuePos(matrix m) {
    int min = m.values[0][0];
    position min_position = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                min_position.rowIndex = i;
                min_position.colIndex = j;
            }
        }
    }

    return min_position;
}

position getMaxValuePos(matrix m) {
    int max = m.values[0][0];
    position max_position = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                max_position.rowIndex = i;
                max_position.colIndex = j;
            }
        }
    }

    return max_position;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, int nMatrices, int nRows, int nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}
