//
// Created by carva on 20/10/2025.
//

#ifndef INC_2526_TI301_PJT_CHAINED_H
#define INC_2526_TI301_PJT_CHAINED_H

#include <stdlib.h>
#include <stdio.h>

struct s_cell{
    int arrival;
    float proba;
    struct s_cell* next;
};
// s_cell is the base cell element for a linked list
typedef struct s_cell t_cell, *p_cell;

struct s_clist{
    p_cell head;
};
// s_clist is the base linked list type
typedef struct s_clist t_clist, *p_clist;

struct s_adjlist{
    p_clist * listarray;
    int len;
};
// s_adjlist is the base adjacency list of clists
typedef struct s_adjlist t_adjlist, *p_adjlist;

p_cell createCell(int, float);
void freeCell(p_cell);

p_clist createCList();
void addCell(p_clist, int, float);
void displayCList(t_clist);
void freeCList(p_clist);

p_adjlist createAdjList(int);
void displayAdjList(t_adjlist);
void freeAdjList(p_adjlist);

#endif //INC_2526_TI301_PJT_CHAINED_H
