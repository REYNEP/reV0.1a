#include <iostream>
#include <cmath>

static struct {
    uint32_t  count[26];
    uint32_t  AVG;
    uint32_t  count_SORTED[26];
} A_TO_Z;

// Also another version, test... czzz alll   n    included, it doesn't go above 10^5
static struct {
    char *S;
    uint32_t length;
} I;

#define ASCII_SMALL_LETTER_START 97

void solveCase(void) {
    std::cin >> I.length;
    //TODO-1: check performance compared to malloc
    //I.S = new char[I.length];
    I.S = static_cast<char *> (malloc(1 * I.length));
    std::cin >> I.S;

    // Initialize to zero
    for (uint32_t i = 0; i < 26; i++) {
        A_TO_Z.count[i] = 0;
    }
    // COUNT A_TO_Z
    for (uint32_t i = 0; i < I.length; i++) {
        A_TO_Z.count[
            I.S[i] - ASCII_SMALL_LETTER_START
        ]++;
    }

    // count_SORTED
    for (uint32_t i = 0; i < 26; i++) {
        A_TO_Z.count_SORTED[i] = A_TO_Z.count[i];
    }
    // BUBBLE SORT
    // TODO Practice Making mergeSort in as less time as I Can
    for (uint32_t lim =  26; lim > 0; lim--) {
        for (uint32_t k = 0; k < lim; k++) {
            if (A_TO_Z.count_SORTED[k]   > A_TO_Z.count_SORTED[k+1]) {
                uint32_t _TMP     = A_TO_Z.count_SORTED[k+1];
                A_TO_Z.count_SORTED[k+1] = A_TO_Z.count_SORTED[k];
                A_TO_Z.count_SORTED[k]   = _TMP;
            }
        }
    }



    // Find the average base point we wanna attack
    double _fAVG = 0;
    double _used_letters_ = 0;
    for (uint32_t i = 0; i < 26; i++) {
        if (A_TO_Z.count_SORTED[i] == 0) {
            continue;
        }
        _used_letters_++;
        _fAVG += (A_TO_Z.count_SORTED[i] * A_TO_Z.count_SORTED[i]);
    }
    _fAVG = _fAVG / _used_letters_;        // 1/26
    A_TO_Z.AVG = static_cast<uint32_t> (round(_fAVG));



    

    // Now we can find the numbers iteams need to be changed
    uint32_t SUM = 0;
    for (int i = 0; i < 26; i++) {
        if (A_TO_Z.count[i] == 0) {
            continue;
        }
        SUM += static_cast<uint32_t> (abs(static_cast<int32_t>(A_TO_Z.AVG - A_TO_Z.count[i])));
    }
    SUM = static_cast<uint32_t> (round(SUM * 0.5));

    std::cout << SUM << " AVG:" << _fAVG;

    free(I.S);
}

int main(void) {
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);

    uint32_t nCases;
    std::cin >> nCases;

    while (nCases--) {
        solveCase();
    }
}