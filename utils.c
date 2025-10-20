#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


adjacency_list readGraph (const char * filename) {
    FILE *file = fopen(filename, "r");
    int nbvert, star, end;
    float proba;
    adjacency_list new_list;

    if (!file) {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }

    if (fscanf(file, "%d", &nbvert) != 1) {
        perror("Could not read the number of vertices");
        exit(EXIT_FAILURE);
    }

    new_list = createList(nbvert);

    while (fscanf(file , "%d %d %d", &star, &end, &proba) == 3) {
        addCell(new_list, end, proba);
    }

    fclose(file);
    return new_list;
}