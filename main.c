#include <stdio.h>
#include "chained.h"
#include "utils.h"

int main() {
    p_adjlist test_adj = createAdjList(3);
    for(int i = 0; i < 3; i++) {
        addCell(test_adj->listarray[i], 1, (float)i/2);
        addCell(test_adj->listarray[i], 2, (float)i/2);
    }

    displayAdjList(*test_adj);
    isMarkov(*test_adj);
    freeAdjList(test_adj);

    printf("This project is still under construction...\n"
           "      ____\n"
           " ____|    \\\n"
           "(____|     `._____\n"
           " ____|       _|___\n"
           "(____|     .'\n"
           "     |____/");
    return 0;
}

