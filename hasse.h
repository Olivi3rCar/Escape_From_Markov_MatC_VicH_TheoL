#ifndef __HASSE_H__
#define __HASSE_H__

#include <stdio.h>
#include <stdlib.h>
#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#include "chained.h"

typedef struct s_tarjan_vertex{
  int id;
  int number;
  int access_number;
  int in_stack_bool;
  } t_tarjan_vertex;

typedef struct s_tarjan_list{
   t_tarjan_vertex * vertices;
  int list_p_len;
  int list_l_len;
} t_tarjan_list;

typedef struct s_class{
  int id;
  t_tarjan_list * list;
  int len;
} t_class;

typedef struct s_partition{
  t_class ** classes;
  int p_len;
  int l_len;
} t_partition;

t_partition * create_partition(int len);

t_tarjan_list * create_filled_tarjan_list(const t_adjlist * adj_list);

t_class * create_class(int edge_size);

typedef struct s_stack_cell{
  t_tarjan_vertex * cell;
  struct s_stack_cell * next;
} t_stack_cell;

typedef struct s_stack_tarjan{
  t_stack_cell * top;
  int logical_size;
  int physical_size;
} t_stack_tarjan;

void parcours(t_tarjan_vertex * vertex, int *num, t_stack_tarjan* stack,
              t_partition* partition, t_adjlist* adj_list, t_tarjan_list* tarjan_list, int * id);
t_partition tarjan_algorithm(t_adjlist* adj_list);

t_stack_tarjan * create_empty_stack(int size);
t_stack_cell* create_cell_stack ();
t_stack_tarjan * push(t_tarjan_vertex *to_be_celled, t_stack_tarjan * stack);
t_tarjan_vertex * pop(t_stack_tarjan * stack);

#endif