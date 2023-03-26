/**
 ██████╗    ██╗███╗   ██╗██████╗ ██╗   ██╗████████╗    ██████╗  █████╗ ███████╗███████╗██████╗ 
██╔════╝    ██║████╗  ██║██╔══██╗██║   ██║╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██╔════╝██╔══██╗
██║         ██║██╔██╗ ██║██████╔╝██║   ██║   ██║       ██████╔╝███████║███████╗█████╗  ██║  ██║
██║         ██║██║╚██╗██║██╔═══╝ ██║   ██║   ██║       ██╔══██╗██╔══██║╚════██║██╔══╝  ██║  ██║
╚██████╗    ██║██║ ╚████║██║     ╚██████╔╝   ██║       ██████╔╝██║  ██║███████║███████╗██████╔╝
 ╚═════╝    ╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝    ╚═╝       ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝╚═════╝ 
                                                                                               

#include "stdio.h"
#include "stdint.h"


char Emiliano_Martinez[400001];     // 4×10⁵: MAX StringLength for 1-TestCase    + 1 for NULL TER
struct {
    uint32_t _CUTS[3];
    uint8_t  _N = 0;
} CAPYBARA;

void solveCase(void) {
    scanf("%s",     Emiliano_Martinez);

    char       f1 = Emiliano_Martinez[0];
    char       f2 = Emiliano_Martinez[1];

    /* WORKS... IG

    if (f1 == f2) {
        CAPYBARA._CUTS[0] = 1;
        CAPYBARA._CUTS[1] = 2;
    }
    else if (f1 < f2) { /** f1 = A **
        CAPYBARA._CUTS[0] = 1;

        char cur;
        for (int i = 2; ; i++) {
            cur = Emiliano_Martinez[i];
            if      (cur == '\0') break;
            else if (cur ==  f2 ) continue;
            else CAPYBARA._CUTS[1] = i;
        }
    }
    else /* if (f1 > f2) * {
        CAPYBARA._CUTS[0] = 1;
        CAPYBARA._CUTS[1] = 2;
    }

    *

    if (f1 < f2) { /** f1 = A **
        CAPYBARA._CUTS[0] = 1;

        char      cur;
        for (int i = 2; ; i++) {
            cur = Emiliano_Martinez[i];
            if      (cur ==  f2 ) continue;
            else if (cur == '\0') {
                CAPYBARA._CUTS[1] = i - 1;      // Hoping that       Emiliano_Martinez[2] != '\0'      I think the questions states that
                break;
            }
            else /* (cur ==  f1 ) * {
                CAPYBARA._CUTS[1] = i;
                break;
            }
        }
    }
    else /* if (f1 > f2) || (f1 == f2) * {
        CAPYBARA._CUTS[0] = 1;
        CAPYBARA._CUTS[1] = 2;
    }

    /*
    for (int i = 1; Emiliano_Martinez[i] != '\0'; i++) {
                    cur = Emiliano_Martinez[i];
        if         (cur == el)  continue;
        else if    (cur <  el)    {el = cur; CAPYBARA._CUTS[CAPYBARA._N] = i; CAPYBARA._N++;}
        else /* if (cur >  el) *  {el = cur;}
    }
    */


    /** PRINT FINAL RESULT.... You can just Collapse this IG.... **
    if (CAPYBARA._N > 2)
        printf(":(");
    else {
        char *_T1 = Emiliano_Martinez;
        char *_T2 = Emiliano_Martinez + CAPYBARA._CUTS[0];
        char *_T3 = Emiliano_Martinez + CAPYBARA._CUTS[1];

        char _T0;
         _T0 = *_T2;
        *_T2 = '\0';
        printf("%s ", _T1);
        *_T2 = _T0;

         _T0 = *_T3;
        *_T3 = '\0';
        printf("%s ", _T2);
        *_T3 = _T0;
        
        printf("%s\n", _T3);
    }
}


uint32_t nCases;
int main(void) {
    scanf("%u", &nCases);

    for (int i = 0; i < nCases; i++) 
        solveCase();
}

*/



/** See if C one can be taken to 15ms with lesser memory... MAYBE CHAR operation is slower than uint32_t..... test that theory */
#include <iostream>

void solveCase(void) {
    std::string Emiliano_Martinez;
    std::cin >> Emiliano_Martinez;
    char   f1 = Emiliano_Martinez[0];
    char   f2 = Emiliano_Martinez[1];

    if (f1 < f2) { /** f1 = A **/
        std::cout << f1 << " ";

        char      cur;
        uint32_t    i = 2;
        uint32_t  len = Emiliano_Martinez.length();
        for(;;i++) {
            cur = Emiliano_Martinez[i];
            if      (cur ==  f2 ) continue;
            else if (  i == len ) {
                std::cout <<  Emiliano_Martinez.substr(1, len-2) << " " << Emiliano_Martinez.substr(len-1) << "\n";
                break;
            }
            else /* (cur ==  f1 ) */ {
                std::cout <<  Emiliano_Martinez.substr(1, i-1) << " " << Emiliano_Martinez.substr(i) << "\n";
                break;
            }
        }
    }
    else /* if (f1 > f2) || (f1 == f2) */ {
        std::cout << f1 << " " << f2 << " " << Emiliano_Martinez.substr(2) << "\n";
    }
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