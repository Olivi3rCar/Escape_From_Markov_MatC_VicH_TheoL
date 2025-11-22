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
    p_clist newl = (p_clist) malloc((sizeof(t_clist)));
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
    while (c != NULL) {c = c->next; freeCell(prev); prev = c;}
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
        freeCList(a->listarray[i]);
    }
    free(a);
}