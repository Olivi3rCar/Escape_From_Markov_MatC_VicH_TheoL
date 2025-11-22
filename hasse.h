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
  } t_tarjan_vertex, * p_tarjan_vertex;

typedef struct s_tarjan_list{
   t_tarjan_vertex * vertices;
  int list_p_len;
  int list_l_len;
} t_tarjan_list, * p_tarjan_list;

typedef struct s_class{
  int id;
  t_tarjan_list * list;
  int len;
} t_class, * p_class;
  t_tarjan_vertex * vertices;
  int len; int id;
} t_class, * p_class;

typedef struct s_partition{
  t_class ** classes;
  int p_len;
  int l_len;
} t_partition, * p_partition;

t_tarjan_list * create_tarjan_list(t_adjlist * adj_list);

typedef struct s_stack_cell{
  t_tarjan_vertex * cell;
  struct s_stack_cell * next;
} t_stack_cell;

typedef struct s_stack_tarjan{
  t_stack_cell * top;
  int logical_size;
  int physical_size;
} t_stack_tarjan, * p_stack_tarjan_vertex;

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
void parcours(t_tarjan_vertex * vertex, int *num, t_stack_tarjan* stack,
              t_partition* partition, t_adjlist* adj_list, t_tarjan_list* tarjan_list, int * id);
t_partition tarjan_algorithm(t_adjlist* adj_list);
/**
 * @brief Modifies a given link array to remove redundancy.
 *
 * @param linkArray pointer to the t_link array to be modified
 * @return The created link array.
 */
void removeTransitiveLinks(p_link_array linkArray);

t_stack_tarjan * create_empty_stack(int size);
t_stack_cell* create_cell_stack ();
t_stack_tarjan * push(t_tarjan_vertex *to_be_celled, t_stack_tarjan * stack);
t_tarjan_vertex * pop(t_stack_tarjan * stack);
/// Frees a transitive link array
/// \param linkArray pointer to the t_link_array to be freed
void freeTransitiveLinks(p_link_array linkArray);

/// Creates and puts the Hasse Diagram of the
/// Current graph present in a txt file
/// into another txt file (dusk.txt)
/// \param part Partition of a Markov graph
void drawHasse(t_partition part);

#endif