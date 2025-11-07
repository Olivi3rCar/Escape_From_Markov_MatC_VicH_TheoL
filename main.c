#include <stdio.h>
#include "chained.h"

int main() {

    p_adjlist new_adj = readGraph("../data/exemple3.txt");

    drawGraph("../data/exemple3.txt");

    displayAdjList(*new_adj);
    isMarkov(*new_adj);
    freeAdjList(new_adj);

    return 0;
}