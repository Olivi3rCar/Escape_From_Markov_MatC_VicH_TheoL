//
// Created by victo on 21/11/2025.
//

#include "chained.h"
#include "hasse.h"

int part2() {

    printf("Let's initialize the graph using a text file form the data directory\n");
    p_adjlist new_adj = readGraph("../data/exemple3.txt");
    printf("\n");

    printf("Let's display the graph:\n");
    displayAdjList(*new_adj);
    printf("\n");




    return 0;
}