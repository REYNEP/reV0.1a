#include <iostream>
#include <cmath>
#include <cstdio>




struct _A_TO_Z_ {
    void Initialize(void) {
        for (uint32_t i = 0; i < 26; i++)
            count[i] = 0;
    }

    void Init_Divisors(uint32_t I_Length) {
        for (uint32_t i = 1; i < 27; i++) {
            if ((I_Length % i) == 0)
                divisors[i] = I_Length / i;
            else
                divisors[i] = 0;
        }
    }

    uint32_t letters_we_have(void) {
        uint32_t _letters_ = 0;
        for (uint32_t i = 0; i < 26; i++) { 
            if (count[i]) 
                _letters_++;
        }
        return   _letters_;
    }

    /** should be called after    \fn Init_Divisors() &   \fn Sort() */
    void Init_Needed(uint32_t number_of_letters) {
        uint32_t number_of_copies_per_letter = divisors[number_of_letters];

        for (uint32_t k = 0; k < number_of_letters; k++) {
             uint32_t i = index_SORTED[k];
            if (count_SORTED[k] == 0) {
                needed[i] = number_of_copies_per_letter;
                excess[i] = 0;
                continue;
            }

            int32_t smth_in_the_way = number_of_copies_per_letter - count[i];
            if (smth_in_the_way > 0) {
                needed[i] = smth_in_the_way;
                excess[i] = 0;
            }
            else {
                needed[i] = 0;
                excess[i] = (0 - smth_in_the_way);
            }
        }

        for (uint32_t k = number_of_letters; k < 26; k++) {
             uint32_t i = index_SORTED[k];
            if (count_SORTED[k] == 0) {
                needed[i] = 0;
                excess[i] = 0;
            }
            else {
                needed[i] = 0;
                excess[i] = count_SORTED[k];
            }
        }
    }
    // it should be above zero at this point
    inline uint32_t next_needed(uint32_t needed_cursor) {
            needed[needed_cursor] -= 1;
        if (needed[needed_cursor]) return needed_cursor;
        else    return Init_Needed_Cursor(needed_cursor+1);
    }

    inline uint32_t Init_Needed_Cursor(uint32_t needed_cursor) {
        for (uint32_t i = needed_cursor; i < 26; i++) {
            if (needed[i])
                return i;
        }
        return 0;
    }

    void Sort(void);

    uint32_t count[26];
    uint32_t count_SORTED[26];              // CALL function Sort... before using this variable
    uint32_t index_SORTED[26];
    uint32_t divisors[27];
    uint32_t divisors_copies_wed_need[27];  // copies we would need if we used that number of letters
    uint32_t needed[26];                    // For Final Thingy
    uint32_t excess[26];
} A_TO_Z;
#define ASCII_SMALL_LETTER_START 97
#define FOREACH_divisor(x) for (uint32_t x = 1; x < 27; x++)
#define min(x, y) ((x > y) ? y : x)

struct {
    char S[100000];     // 10⁵  lets just say... someone inputs that many
    char O[100000];
    uint32_t length;
} I;






/**
 *  PATCH-1: Memory optimizations & running it on GCC... instead of MSVC
 */
void solveCase(char *S, char *O) {
                        /** I.S = new char[I.length+1];  */ S[I.length] = '\0';
    scanf("%s", S);     /** I.O = new char[I.length+1];  */ O[I.length] = '\0';

    /** Initialize & Count A_TO_Z */
    A_TO_Z.Initialize();
    for (uint32_t i = 0; i < I.length; i++) {
        A_TO_Z.count[
            S[i] - ASCII_SMALL_LETTER_START
        ]++;
    }
    /** SORT & Find the divisors */
    A_TO_Z.Sort();
    A_TO_Z.Init_Divisors(I.length);

    /**
    for (uint32_t i = 0; i < 26; i++) {
        std::cout << A_TO_Z.index_SORTED[i] << ", ";
    }
    std::cout << std::endl;
    */



    /** Find 'number_of_letters' we wanna use */
    uint32_t number_of_letters = 1;
    FOREACH_divisor(di) {
        // If Divisible
        if (A_TO_Z.divisors[di]) {
          //uint32_t number_of_letters = di;
            uint32_t number_of_copies_per_letter = A_TO_Z.divisors[di];

            uint32_t number_of_copies_we_already_have = 0;
             int32_t number_of_copies_excessive = 0;

            for (uint32_t i = 0; i < di; i++) {
                // Since its sorted things on the right is gonna be zero
                if (A_TO_Z.count_SORTED[i] == 0)
                    break;

                /**
                int32_t smth_in_the_way = static_cast<int32_t>(A_TO_Z.count_SORTED[i]) - static_cast<int32_t>(number_of_copies_per_letter);
                if (smth_in_the_way < 0) {
                    if (number_of_copies_excessive > 0) {
                        number_of_copies_excessive   -= smth_in_the_way;
                    number_of_copies_we_already_have 
                    }
                    else
                    number_of_copies_we_already_have += A_TO_Z.count_SORTED[i];
                }
                else {
                    number_of_copies_we_already_have += number_of_copies_per_letter;
                    number_of_copies_excessive       += smth_in_the_way;
                }
                */
                number_of_copies_we_already_have += min(A_TO_Z.count_SORTED[i], number_of_copies_per_letter);
            }

            // A.K.A we would need to change those
                A_TO_Z.divisors_copies_wed_need[di] = I.length - number_of_copies_we_already_have;
              //A_TO_Z.divisors_copies_wed_need[di] = abs(static_cast<int32_t> (0 - number_of_copies_excessive));

            if (A_TO_Z.divisors_copies_wed_need[di] < A_TO_Z.divisors_copies_wed_need[number_of_letters])
                number_of_letters = di;

          //std::cout << "DIVISOR: " << di << " " << " COPIES: " << A_TO_Z.divisors_copies_wed_need[di] << std::endl;
        }
    }


    A_TO_Z.Init_Needed(number_of_letters);
    /** Final thingy */
    uint32_t needed_cursor = A_TO_Z.Init_Needed_Cursor(0);
    for (uint32_t i = 0; i < I.length; i++) {
         uint32_t S_index = S[i] - ASCII_SMALL_LETTER_START;

        if (A_TO_Z.excess[S_index]) {
            A_TO_Z.excess[S_index]--;
            O[i] = needed_cursor + ASCII_SMALL_LETTER_START;
            needed_cursor = A_TO_Z.next_needed(needed_cursor);
        }
        else {
            O[i] = S[i];
        }
      //std::cout << A_TO_Z.needed[needed_cursor] << std::endl << O << std::endl;
    }



    //std::cout << "DIVISOR: " << number_of_letters << " " << " COPIES: " << A_TO_Z.divisors_copies_wed_need[number_of_letters] << std::endl;
    std::cout << A_TO_Z.divisors_copies_wed_need[number_of_letters] << std::endl << O << std::endl;
    //delete I.S;
    //delete I.O;
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














void _A_TO_Z_::Sort(void) {
    for (uint32_t i = 0; i < 26; i++) {
        count_SORTED[i] = count[i];
        index_SORTED[i] = i;
    }

    // BUBBLE SORT (TO THE LEFT)
    // TODO Practice Making mergeSort in as less time as I Can
    for (uint32_t     lim = 0; lim < 26; lim++) {
        for (uint32_t k = lim;   k > 0; k--) {
            if (count_SORTED[k]   > count_SORTED[k-1]) {
                // SWAP
                uint32_t _TMP     = count_SORTED[k-1];
                count_SORTED[k-1] = count_SORTED[k];
                count_SORTED[k]   = _TMP;

                _TMP              = index_SORTED[k-1];
                index_SORTED[k-1] = index_SORTED[k];
                index_SORTED[k]   = _TMP;
                // SWAP
            }
        }
    }
}