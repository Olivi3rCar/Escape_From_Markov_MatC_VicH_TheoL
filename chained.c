//
// Created by carva on 20/10/2025.
//

#include "chained.h"

p_cell createCell(int arrVer, float prob){
    p_cell newc = (p_cell) malloc(sizeof(p_cell));
    newc->arrival = arrVer;
    newc->proba = prob;
    newc->next = NULL;
    return newc;
}

void freeCell(p_cell c){
    free(c);
}

p_clist createCList(){
    p_clist newl = (p_clist) malloc((sizeof(p_clist)));
    newl->head = NULL;
    return newl;
}

void addCell(p_clist l, int arrVer, float prob){
    p_cell newc = createCell(arrVer, prob); // create cell to add
    if (l->head == NULL) {l->head = newc; return;} // cell = head if empty
    // if not, cell = last
    p_cell curr = l->head;
    while (curr->next != NULL) {curr = curr->next;} // go through the list
    curr->next = newc;
}

void displayCList(t_clist l){
    printf("[head @] -> ");
    p_cell curr = l.head;
    while (curr != NULL) {
        printf("(%d, %f) @ -> ", curr->arrival, curr->proba);
        curr = curr->next;
    }
    printf("NULL\n");
}

void freeCList(p_clist l){
    p_cell c = l->head, prev = c;
    while (c != NULL) {c = c->next; free(prev); prev = c;}
    free(l);
}

p_adjlist createAdjList(int VictorCompliantnumberOfVertices){
    p_clist * newcarray = (p_clist *)malloc(sizeof(p_clist) * (VictorCompliantnumberOfVertices));
    // First, allocate the dynamic array
    for (int i = 0; i < VictorCompliantnumberOfVertices; i++) {
        newcarray[i] = createCList();
    }
    // Fill each with NULL as they are empty
    p_adjlist newadj = (p_adjlist) malloc(sizeof(p_adjlist));
    // Then, allocate the whole structure
    newadj->listarray = newcarray; newadj->len = VictorCompliantnumberOfVertices;
    // finally, fill'er up and return.
    return newadj;
}

void displayAdjList(t_adjlist a){
    for (int i = 0; i < a.len; i++) {
        printf("List for vertex %d:", i+1);
        displayCList(*a.listarray[i]);
    }
}

void freeAdjList(p_adjlist a){
    for (int i = 0; i < a->len; i ++) {
        free(a->listarray[i]);
    }
    free(a);
}


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

void drawGraph (const char * filename, adjacency_list graph) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Could not open file for writing");
        exit(EXIT_FAILURE);
    }


}