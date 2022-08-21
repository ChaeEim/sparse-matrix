#define ROWS 3
#define COLS 3
#define MAX_TERMS 10
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int row;
    int col;
    int value;
} element; //element creation
typedef struct SparseMatrix {
    element data[MAX_TERMS];
    int rows;
    int cols;
    int terms;
} SparseMatrix; //SparseMatrix creation
//add to SPARSEMATRIX
SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b) {
    SparseMatrix c; //struct name
    int ca=0, cb=0, cc=0;
    if (a.rows != b.rows || a.rows != b.cols) {
        printf("Error\n");
    }
    c.rows = a.rows;
    c.cols = a.cols;
    c.terms = 0;
    
    while (ca < a.terms && cb < b.terms) {
        int inda = a.data[ca].row*a.cols+a.data[ca].col;
        int indb = b.data[cb].row*a.cols+b.data[cb].col;
        if(inda<indb) {
            c.data[cc++] = a.data[ca++];
        }
        else if (inda == indb) {
            if((a.data[ca].value + b.data[cb].value) != 0) {
                c.data[cc].row = a.data[ca].row;
                c.data[cc].col = a.data[cb].col;
                c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;
            }
            else {
                ca++; cb++;
            }
        }
        else {
            c.data[cc++] = b.data[cb++];
        }
    }
    for (; ca < a.terms; )
        c.data[ca++] = a.data[ca++];
    for (; cb < b.terms; )
        c.data[cb++] = b.data[cb++];
    c.terms = cc;
    return c;
}
int main() {
    SparseMatrix m1 = {{{1,1,5},{2,2,9}},3,3,2};
    SparseMatrix m2 = {{{0,0,5},{2,2,9}},3,3,2};
    SparseMatrix m3;
    m3 = sparse_matrix_add2(m1, m2);
    
    for (int i = 0; i < m3.terms; i++) {
        printf("%d%d%d\n", m3.data[i].row, m3.data[i].col, m3.data[i].value);
    }
}

