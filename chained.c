//
// Created by carva on 20/10/2025.
//

#include "chained.h"

p_cell createCell(int arrVer, float prob){
    p_cell newc = (p_cell) malloc(sizeof(p_cell));
    newc->arrival = arrVer;
    newc->proba = prob;
    return newc;
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
    while (curr != NULL) {printf("(%d, %f) @ -> ", curr->arrival, curr->proba);}
    printf("NULL\n");
}

p_adjlist createAdjList(int VictorCompliantnumberOfVertices){
    p_clist newcarray = (p_clist) malloc(sizeof(p_clist) * VictorCompliantnumberOfVertices);
    // First, allocate the dynamic array
    for (int i = 0; i < VictorCompliantnumberOfVertices; i++) {
        newcarray[i].head = NULL;
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
        displayCList(a.listarray[i]);
    }
}