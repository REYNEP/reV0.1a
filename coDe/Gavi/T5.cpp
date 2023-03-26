#include <iostream>
#include "stdint.h"

/**
 * @param PTR: should be at least N sized
 * @param BUF: should be at least N sized.... tho values can be undefined
 * @param   N: the size.... you know
 */
void REY_MergeSort(uint32_t *PTR, uint32_t *BUF, uint32_t N) {
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
    uint32_t   _cursor = 0;
    uint32_t  A_cursor = 0;
    uint32_t  D_cursor = 0;
    uint32_t  A_end = (N >> 1) + (N & 1);   // More Like A_N
    uint32_t  D_end = (N >> 1);             // More like D_N
    uint32_t *A_ptr = PTR;
    uint32_t *D_ptr = PTR + A_end;

    //REY_MergeSortLEFT()
    REY_MergeSort(A_ptr, BUF, A_end);
    //REY_MergeSortRIGHT()
    REY_MergeSort(D_ptr, BUF, D_end);

    //REY_Merge()
    for(uint32_t I = N; I > 0; I--) {
        uint32_t A = A_ptr[A_cursor];
        uint32_t D = D_ptr[D_cursor];

        if (A < D) {
            BUF[_cursor++] = A;
            A_cursor++;
            if (A_cursor >= A_end) { memcpy(&BUF[_cursor], &D_ptr[D_cursor], sizeof(uint32_t) * I); break; }
        }
        else {
            BUF[_cursor++] = D;
            D_cursor++;
            if (A_cursor >= A_end) { memcpy(&BUF[_cursor], &A_ptr[A_cursor], sizeof(uint32_t) * I); break; }
        }
    }
    memcpy(PTR, BUF, N * sizeof(uint32_t));
}

inline void REY_GET_INPUT_LIST(uint32_t *PTR, uint32_t N) {
    for (uint32_t i = 0; i < N; i++) {
        std::cin >> PTR[i];
    }
}

/** 
 * GCC could have failed earlier.... cz of of---- 
 * 1. static struct.....   (czzz it worked on MSVC)
 * 2. some memory leak.... (can I really use Valgrind???   >_<   )
 * 3. new uint32[N]
 * 4. functions inside struct... & definitions like heck.... i never used those outside of amGHOST / amVK
 */
void solveCase(void) {
    uint32_t    N; std::cin >> N;
    uint32_t *PTR; PTR = static_cast<uint32_t *> (malloc(sizeof(uint32_t) * N));
    uint32_t *BUF; BUF = static_cast<uint32_t *> (malloc(sizeof(uint32_t) * N));
    REY_GET_INPUT_LIST(PTR, N);

    // We can't get that UNSORTED_PTR.... anymore....
    REY_MergeSort(PTR, BUF, N);
    //for (uint32_t i = 0; i < N; i++) {
    //    std::cout << PTR[i] << ", ";
    //}

    uint32_t         can_we_go_to_the_cinema;       // conditionn: no one must be SAD >_<
    if (PTR[0] > 0) {can_we_go_to_the_cinema = 1;}  // even if no one goes to movie .... noone will be SAD xD
    else            {can_we_go_to_the_cinema = 0;}

    // i gotta BE more CAREFUL about using 'uint32_t' czzz it can't become negative
    for (uint32_t I = 0; I < N;) {
        if (PTR[I] <= I) {
            can_we_go_to_the_cinema++;
            I++;
            // We can, but gotta take the NEXT ones that wanna go....
            while( (PTR[I] <= I) && (I<N) ) I++;
        }
        else I++;
    }

    std::cout << can_we_go_to_the_cinema << std::endl;
    free(PTR); free(BUF);
}

int main(void) {
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);

    uint32_t nCases;
    std::cin >> nCases;

    while(nCases--) {
        solveCase();
    }
}