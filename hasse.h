#ifndef INC_2526_TI301_PJT_HASSE_H__
#define INC_2526_TI301_PJT_HASSE_H__

#include <stdio.h>
#include <stdlib.h>
#include "chained.h"

typedef struct s_tarjan_vertex{
  int id;
  int number;
  int access;
  int bool;
} t_tarjan_vertex, * p_tarjan_vertex;

typedef struct s_tarjan_list{
   t_tarjan_vertex * vertices;
} t_tarjan_list, * p_tarjan_list;

typedef struct s_class{
  t_tarjan_vertex * vertices;
  int len; int id;
} t_class, * p_class;

typedef struct s_partition{
  t_class * classes;
  int len;
} t_partition, * p_partition;

t_tarjan_list * create_tarjan_list(t_adjlist * adj_list);

typedef struct s_stack_cell{
  t_tarjan_list cell;
  t_tarjan_list * next;
} t_stack_cell, * p_stack_cell;

typedef struct s_stack_tarjan_vertex{
  t_stack_cell * cells;
  t_stack_cell * head;
  t_stack_cell * tail;
} t_stack_tarjan_vertex, * p_stack_tarjan_vertex;

typedef struct s_link{
    int from, to;
} t_link, *p_link;

typedef struct s_link_array{
    p_link arr; int len; int log_size;
} t_link_array, *p_link_array;

p_class link_vertex_to_class(t_adjlist vertices, t_partition part);

/// Creates and returns a pointer to a Transitive Link array
/// of type t_link_array
/// \param part The partition of the graph of which we want to get the list
/// \return The newly created link array
p_link_array createTransitiveLinks(t_adjlist vertices, t_partition part);

/**
 * @brief Modifies a given link array to remove redundancy.
 *
 * @param linkArray pointer to the t_link array to be modified
 * @return The created link array.
 */
void removeTransitiveLinks(p_link_array linkArray);

/// Frees a transitive link array
/// \param linkArray pointer to the t_link_array to be freed
void freeTransitiveLinks(p_link_array linkArray);

/// Creates and puts the Hasse Diagram of the
/// Current graph present in a txt file
/// into another txt file (dusk.txt)
/// \param part Partition of a Markov graph
void drawHasse(t_partition part);

#endif