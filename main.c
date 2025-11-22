#include <stdio.h>
#include "chained.h"
#include "hasse.h"


int main() {

    printf("Let's initialize the graph using a text file form the data directory\n");
    p_adjlist new_adj = readGraph("../data/exemple3.txt");
    printf("\n");

    printf("Let's display the graph:\n");
    displayAdjList(*new_adj);
    printf("\n");

    t_partition partition = tarjan_algorithm(new_adj);

    // printf("But is this matrix a Markov graph ? If not, why ?:\n");
    // isMarkov(*new_adj);
    // printf("\n");
    //
    // printf("Fine, now, create a file to display it in Mermaid:\n");
    // drawGraph("../data/exemple3.txt");


    freeAdjList(new_adj);
    return 0;
}