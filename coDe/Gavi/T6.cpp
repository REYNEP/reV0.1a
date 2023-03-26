#include <iostream>
#include <map>
#include "stdint.h"
#include "math.h"

//#define EXTENDED_CUT

#define REY_IS_ODD(x) (x & 1)
inline void REY_GET_INPUT_LIST(uint32_t *PTR, uint32_t N) {
    for (uint32_t i = 0; i < N; i++) {
        std::cin >> PTR[i];
    }
}

uint32_t INP[50];
void solveCase(void) {
    uint32_t N; std::cin >> N;
    REY_GET_INPUT_LIST(INP, N);                 // uint32_t  a < 10^9

    std::map<uint64_t, uint64_t> Z;
    std::map<uint64_t, uint64_t> one_run;

    // numbers are already sorted from smaller to big
    for    (uint32_t I =   0; I < N; I++) {     // N <= 50
        for(uint32_t K = I+1; K < N; K++) {     // N <= 50
            uint32_t A = INP[I];
            uint32_t D = INP[K];
            uint32_t DIFF = D - A;
          //if (DIFF == 0)                      //Question specifies it wont happen, but 
          //    WHATEVER.... instead of 'Z[x.first] = x.second + 1;' below would have to change '1' to 'XD = 1'       aaand in this line XD++;
            if (DIFF <= 2) continue;
            uint32_t DIFF_sqrt = sqrt(DIFF);
            std::cout << " DIFF_sqrt:" << DIFF_sqrt << " A:" << A << " D:" << D << " DIFF:" << DIFF;
            
            if (!REY_IS_ODD(DIFF)) {
                // FindDiv()
                // FindDiv(36) 3x12              [10 + 12 + 14] = 36 no other 3 numbers can do that....
                // if     DIFF == EVEN     & i == ODD,   then QUOTIENT == EVEN
                for (uint32_t i = 2; i <= DIFF_sqrt; i+=2) {
                    std::cout << " i:" << i;
                    if ((DIFF % i) == 0) {
                        uint32_t Quotient =(DIFF / i);

                      //FindDiv(36) 4x9   [wont work] => [6 + 8 + 10 + 12] = 36   but square numbers dont have even DIFF
                      // these are the only 4 consecutive numbers to make up 36   but this indicates that,   [read back]
                        if (Quotient & 1) continue;
                        if (Quotient < i) break;
                      // Anyway this is proly the last case... whatever, still validation

                      //FindDiv(36) 6x6          [1 + 3 + 5 + 7 + 9  + 11] = 36
                      //uint32_t X  = Quotient - 1 - (i - 2);
                      //uint32_t Xx = X >> 1;
                        uint32_t Xx =(Quotient - 1 - (i - 2)) >> 1;
                      //FindDiv(36) 6x6          Xx == 0; X = 1;
                        if (!Xx) break;
                      // Anyway this is proly the last case... whatever, still validation

                      //FindDiv(48) 6x8          [3 + 5 + 7 + 9 + 11 + 13] = 48
                        uint64_t Xx_pow2 = Xx * Xx;
                        std::cout << " Xx_pow2:" << Xx_pow2;
                        if (A <= Xx_pow2)
                            one_run[Xx_pow2 - A]++;
                        else
                            break;              // we dont need to check anymore, next 
                    }
                }
            }
            else {
                if (DIFF < 3) continue;         //FailSafe

                for (uint32_t i = 1; i <= DIFF_sqrt; i+=2) {
                    #ifdef EXTENDED_CUT
                    std::cout << " i:" << i;
                    #endif
                    if ((DIFF % i) == 0) {
                        #ifndef EXTENDED_CUT
                        std::cout << " i:" << i;
                        #endif
                        uint32_t Quotient =(DIFF / i);
                        uint32_t Xx =(Quotient + 1 - (i    )) >> 1;

                        uint64_t Xx_pow2 = Xx * Xx;
                        std::cout << " Xx_pow2:" << Xx_pow2;
                        if (A <= Xx_pow2)
                            one_run[Xx_pow2 - A]++;
                        else
                            break;              // we dont need to check anymore, next 
                    }
                }
            }
            std::cout << std::endl;
        }

        // After each run... or all found Z values.... we increment for 'I'
        for (auto& x: one_run) {
            std::cout << x.first << ": " << x.second << '\n';
            if (Z[x.first] < x.second)
                Z[x.first] = x.second + 1;
        }

        one_run.clear();
    }

    uint32_t ANS = 1;
    for (auto& x: Z) {
        std::cout << x.first << ": " << x.second << '\n';
        if (ANS < x.second)
            ANS = x.second;
    }

    std::cout << ANS << std::endl;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t nCases;
    std::cin >> nCases;

    while(nCases--) {
        solveCase();
    }
}