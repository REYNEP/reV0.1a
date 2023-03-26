#include <iostream>
#include <vector>
#include <map>
#ifdef REY_TIMER_INCLUDE

#include <chrono>
#define REY_TIMER_BEGIN std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
#define REY_TIMER_END   std::chrono::steady_clock::time_point   end = std::chrono::steady_clock::now();
#define REY_TIMER_PRINT \
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl; \
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl; \
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl; \

#endif




void solveCase(void) {
    //uint32_t            *PTR = static_cast<uint32_t *>  (calloc(400000, 4));
    std::map<uint32_t, uint32_t> PTR;
    uint32_t    nIntegers;
    std::cin >> nIntegers;
    //uint32_t   **INT_TABLE = static_cast<uint32_t **> (malloc(nIntegers * 8));
    //uint32_t   *_N_INT_TABLE = static_cast<uint32_t *>  (malloc(nIntegers * 4));
    //uint32_t      *INT_TABLE = static_cast<uint32_t *>  (malloc(100000 * 4));
    std::vector<std::vector<uint32_t>> INT_TABLE(nIntegers);

    uint32_t lim;
   // uint32_t *muhaha = INT_TABLE;
    uint32_t cur;
    for (    uint32_t i = 0; i < nIntegers; i++) {
        std::cin >> lim;
        //_N_INT_TABLE[i] = lim;
        //INT_TABLE[i] = static_cast<uint32_t *>  (malloc(lim * 4));
        INT_TABLE[i].resize(lim);
        
        // muhaha = INT_TABLE[i];
        // MUHAHA, cur
        //for (uint32_t k = 0; k < lim; k++) {
        //    std::cin >> cur;
        //    INT_TABLE[i][k] = cur;
        //    //*muhaha++ = cur;
        //    PTR[cur]++;
        //}

        for (auto &x : INT_TABLE[i]) {
            std::cin >> x;
            PTR[x]++;
        }
    }

    //muhaha = INT_TABLE;
    bool PRINTED_YES = false;
    for (    uint32_t i = 0;                        i < nIntegers; i++) {
        uint32_t ok = 1;
        //for (uint32_t k = 0, lim = INT_TABLE[i].size(); k < lim;       k++) {
        //    if (PTR[INT_TABLE[i][k]] > 1)
        //        continue;
        //   else {
        //        ok = false;
        //        break;
        //    }
        //}
        for (auto x: INT_TABLE[i]) {
            if (PTR[x] == 1) {
                ok = 0;
                break;
            }
        }

        if (ok == true) {
            std::cout << "YES\n";
            return;
            //while(i < nIntegers) 
            //    free(INT_TABLE[i++]);
        }
        //free(INT_TABLE[i]);

        
    }

    if (!PRINTED_YES) {
        std::cout << "NO\n";
    }

    //free(_N_INT_TABLE);
    //free(INT_TABLE);
    //free(PTR);
    return;
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