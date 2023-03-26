#include <iostream>
#include <cmath>

void solveCase(void) {
    uint32_t N, K, ANS = 0, OK = 0; std::cin >> N;

    for (uint32_t i = 1; i <= N; i++) {
        std::cin >> K;

        if (i == K)
            OK++;

        uint32_t DIFF = abs(static_cast<int32_t>(i) - static_cast<int32_t>(K));
        if(ANS < DIFF)
           ANS = DIFF;
    }

    if (ANS > 0)
        ANS++;

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

    return 0;
}