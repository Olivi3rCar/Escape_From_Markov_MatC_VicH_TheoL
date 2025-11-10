#ifndef __HASSE_H__
#define __HASSE_H__

#include <stdio.h>
#include <stdlib.h>
#include "chained.h"

typedef struct s_tarjan_vertex{
  int id;
  int number;
  int access;
  int bool;
  } t_tarjan_vertex;

typedef struct s_tarjan_list{
   t_tarjan_vertex * vertices;
   } t_tarjan_list;

typedef struct s_class{
  char * name;
  t_tarjan_vertex * vertices;
} t_class;

typedef struct s_partition{
  t_class * classes;
} t_partition;

t_tarjan_list * create_tarjan_list(t_adjlist * adj_list);

typedef struct s_stack_cell{
  t_tarjan_list cell;
  t_tarjan_list * next;
} t_stack_cell;

typedef struct s_stack_tarjan{
  t_stack_cell * cells;
  t_stack_cell * head;
  t_stack_cell * tail;
} t_stack_tarjan;

void parcours(t_tarjan_vertex * vertex, int num, t_stack_tarjan* stack, t_partition* partition);

t_stack_tarjan * push(t_stack_cell *cell, t_stack_tarjan * stack);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */
//void removeTransitiveLinks(t_link_array *p_link_array);


#endif