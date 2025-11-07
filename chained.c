//
// Created by carva on 20/10/2025.
//

#include "chained.h"

p_cell createCell(int arrVer, float prob){
    p_cell newc = (p_cell) malloc(sizeof(t_cell));
    newc->arrival = arrVer;
    newc->proba = prob;
    newc->next = NULL;
    return newc;
}

void freeCell(p_cell c){
    free(c);
}

p_clist createCList(){
    p_clist newl = (p_clist) malloc(sizeof(t_clist));
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
        printf("(%d, %.2f) @ -> ", curr->arrival, curr->proba);
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
    p_clist * newcarray = (p_clist *)malloc(sizeof(t_clist) * (VictorCompliantnumberOfVertices));
    // First, allocate the dynamic array
    for (int i = 0; i < VictorCompliantnumberOfVertices; i++) {
        newcarray[i] = createCList();
    }
    // Fill each with NULL as they are empty
    p_adjlist newadj = (p_adjlist) malloc(sizeof(t_adjlist));
    // Then, allocate the whole structure
    newadj->listarray = newcarray;
    newadj->len = VictorCompliantnumberOfVertices;
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

void isMarkov(t_adjlist Markov){
    for (int i = 0; i < Markov.len; i++) {
        p_cell tmp = Markov.listarray[i]->head;
        float total = 0;
        while (tmp!=NULL) {
            total += tmp->proba;
            tmp = tmp->next;
        }
        if (total>1.0 || total<0.99) {
            printf("The graph is not a Markov graph \nThe sum of the probabilities of vertex %d is %.2f\n", i+1,total);
            return;
        }
    }
    printf("The graph is a Markov graph\n");
    return;
}


p_adjlist readGraph (const char * filename) {
    FILE *file = fopen(filename, "r");
    int nbvert, start, end;
    float proba;
    p_adjlist new_list;

    if (!file) {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }

    if (fscanf(file, "%d", &nbvert) != 1) {
        perror("Could not read the number of vertices");
        exit(EXIT_FAILURE);
    }

    new_list = createAdjList(nbvert);

    while (fscanf(file , "%d %d %f.2", &start, &end, &proba) == 3) {
        addCell(new_list->listarray[start-1], end, proba);
    }

    fclose(file);
    printf("File read successfully\n");
    return new_list;
}

void drawGraph (const char * filename) {
    FILE *input = fopen(filename, "r");
    FILE *output = fopen("../data/ariel.txt", "w");

    if (!input) {
        perror("Could not open the file for reading");
        exit(EXIT_FAILURE);
    }
    if (!output) {
        perror("Could not open/create the file for writing");
        exit(EXIT_FAILURE);
    }


    fprintf(output, "---\n"
                        "config:\n"
                        "    layout: elk\n"
                        "    theme: neo\n"
                        "    look: neo\n"
                        "---\n\n"
                        "flowchart LR\n");


    p_adjlist list = readGraph(filename);

    ///Writing all the differents nodes
    for (int i = 0; i < list->len; i++) {
        fprintf(output, "%s((%d))\n",getID(i+1),i+1);
    }
    fprintf(output, "\n");

    ///Linking the nodes
    for (int i = 0; i < list->len; i++) {
        p_cell tmp = list->listarray[i]->head;
        while (tmp!=NULL) {
            fprintf(output, "%s -->|%.2f|",getID(i+1), tmp->proba);
            fprintf(output, "%s\n", getID(tmp->arrival));
            tmp = tmp->next;
        }
    }

    fclose(input);
    fclose(output);
    free(list);
    printf("The file has been successfully outputed here: Escape_From_Markov_MatC_VicH_TheoL/data/ariel.txt\n");
    return;
}