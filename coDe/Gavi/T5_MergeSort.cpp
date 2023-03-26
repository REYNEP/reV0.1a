#include "stdint.h"
#include "string.h"
#include <iostream>

//int table[8] = {5, 6, 7, 8, 1, 2, 3, 4};
int table[8] = {5, 1, 8, 4, 2, 7, 3, 6};
int table_SORTED[8];

void REY_MergeSort(int *PTR, int *BUF, uint32_t N) {
    if (N == 1) {return;}
    else if (N == 2) {
        if (PTR[0] < PTR[1])
            return;
        else {
            int TMP = PTR[1];
            PTR[1] = PTR[0];
            PTR[0] = TMP;
        }
        return;
    }
    // REY_Variables
    uint32_t   _cursor = 0;
    uint32_t  A_cursor = 0;
    uint32_t  D_cursor = 0;
    uint32_t  A_end = (N >> 1) + (N & 1);
    uint32_t  D_end =  N >> 1;
    int      *A_ptr = PTR;
    int      *D_ptr = PTR + A_end;

    //REY_MergeSortLEFT();
    REY_MergeSort(A_ptr, BUF, A_end);  // bit-shift or divide by zero
    //REY_MergeSortRIGHT();
    REY_MergeSort(D_ptr, BUF, D_end);


    //REY_Merge();
    for(uint32_t i = N; i > 0; i--) {
        uint32_t A = A_ptr[A_cursor];
        uint32_t D = D_ptr[D_cursor];

        if (A < D) {
            BUF[_cursor++] = A;
            A_cursor++;
            if (A_cursor >= A_end) {memcpy(&BUF[_cursor], &D_ptr[D_cursor], sizeof(int) * (i)); break;}
        }
        else {
            BUF[_cursor++] = D;
            D_cursor++;
            if (D_cursor >= D_end) {memcpy(&BUF[_cursor], &A_ptr[A_cursor], sizeof(int) * (i)); break;}
        }
    }
    memcpy(PTR, BUF, N * sizeof(int));
}

int main(void) {
    for (uint32_t i = 0; i < 9; i++) {
        std::cout << table[i] << ", ";
    }

    REY_MergeSort(table, table_SORTED, 9);

    for (uint32_t i = 0; i < 9; i++) {
        std::cout << table[i] << ", ";
    }
    std::cout << std::endl;
}