#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chained.h"

#include "utils.h"

static char *getID(int i)
{
    // translate from 1,2,3, .. ,500+ to A,B,C,..,Z,AA,AB,...
    static char buffer[10];
    char temp[10];
    int index = 0;

    i--; // Adjust to 0-based index
    while (i >= 0)
    {
        temp[index++] = 'A' + (i % 26);
        i = (i / 26) - 1;
    }

    // Reverse the string to get the correct order
    for (int j = 0; j < index; j++)
    {
        buffer[j] = temp[index - j - 1];
    }
    buffer[index] = '\0';

    return buffer;
}


p_adjlist readGraph (const char * filename) {
    FILE *file = fopen(filename, "r");
    int nbvert, star, end;
    float proba;

    if (!file) {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }

    if (fscanf(file, "%d", &nbvert) != 1) {
        perror("Could not read the number of vertices");
        exit(EXIT_FAILURE);
    }

    p_adjlist new_list = createAdjList(nbvert);

    while (fscanf(file , "%d %d %d", &star, &end, &proba) == 3) {
        addCell(new_list->listarray[star], end, proba);
    }

    fclose(file);
    return new_list;
}

void drawGraph (const char * filename, p_adjlist graph) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Could not open file for writing");
        exit(EXIT_FAILURE);
    }


}

void isMarkov(t_adjlist Markov){
    for (int i = 0; i < Markov.len; i++) {
        p_cell tmp = Markov.listarray[i]->head;
        float total = 0;
        while (tmp!=NULL) {
            total += tmp->proba;
            tmp = tmp->next;
        }
        if (total>1.0 || total<0.99) {
            printf("The graph is not a Markov graph \nthe sum of the probabilities of vertex %d is %f\n", i,total);
            return;
        }
    }
    printf("The graph is a Markov graph\n");
    return;
}
