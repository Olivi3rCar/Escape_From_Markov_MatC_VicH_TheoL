#include "hasse.h"

t_tarjan_list * create_filled_tarjan_list(t_adjlist * adj_list){
  t_tarjan_list * tarjan_list = malloc(sizeof(t_tarjan_list));
  if(tarjan_list == NULL){
    printf("Memory allocation failed in create_tarjan_list\n");
    exit(1);
  }

  tarjan_list->vertices = malloc(adj_list->len * sizeof(t_tarjan_vertex));
  if(tarjan_list->vertices == NULL){
    printf("Memory allocation failed in create_tarjan_list during vertices allocation\n");
    exit(1);
  }

  for(int i = 0; i < adj_list->len; i++){
	  tarjan_list->vertices[i].id = i;
   	tarjan_list->vertices[i].number = -1;
   	tarjan_list->vertices[i].access_number = -1;
    tarjan_list->vertices[i].in_stack_bool = -1;
  }

  return tarjan_list;
}

t_class * create_class(int edge_size){
  t_tarjan_list * tar_list = malloc(edge_size*sizeof(t_tarjan_vertex*));
  t_class * new_class = malloc(sizeof(t_class));
  if(new_class == NULL || tar_list == NULL){
    printf("Memory allocation failed in create_class\n");
    exit(1);
  }
  new_class->list = tar_list;
  new_class->len = edge_size;
  return new_class;
}

t_partition * create_partition(int len){
  t_partition * new_partition = malloc(sizeof(t_partition));
  new_partition->classes = malloc(len*sizeof(t_class*));
  if(new_partition->classes == NULL || new_partition == NULL){
    printf("Memory allocation failed in create_partition\n");
    exit(1);
  }
  return new_partition;
}

t_stack_cell* create_cell_stack (t_stack_tarjan * stack){
  t_stack_cell* cell = (t_stack_cell*) malloc(sizeof(t_stack_cell));
  if(cell == NULL){
    printf("Memory allocation failed in stack_create_cell\n");
    exit(1);
  }
  return cell;
}

t_stack_tarjan * create_empty_stack(int size){
  t_stack_tarjan * stack = malloc(sizeof(t_stack_tarjan));
  if(stack == NULL){
    printf("Memory allocation failed in create_empty_stack\n");
    exit(1);
  }
  stack->top=NULL;
  stack->physical_size=size;
  stack->logical_size=0;
  return stack;
}

t_stack_tarjan * push(t_tarjan_vertex *to_be_celled, t_stack_tarjan * stack){
  if (stack->logical_size == stack->physical_size) {
    printf("Stack is full\n");
    return stack;
  }
  t_stack_cell * new_cell = create_cell_stack(stack);
  new_cell->cell = to_be_celled;
  if (stack->logical_size == 0){
    stack->top = new_cell;
    stack->logical_size++;
    new_cell->next=NULL;
  }
  else {
    stack->logical_size++;
    new_cell->next=stack->top;
    stack->top=new_cell;
  }
  return stack;
}

t_tarjan_vertex * pop(t_stack_tarjan * stack){
  t_tarjan_vertex * vertex = stack->top->cell;
  stack->top=stack->top->next;
  stack->logical_size--;
  return vertex;
}

void parcours(t_tarjan_vertex * vertex, int *num, t_stack_tarjan* stack,
              t_partition* partition, t_adjlist* adj_list, t_tarjan_list* tarjan_list, int * id){
  vertex->number = *num;
  vertex->access_number = *num;
  num++;
  push(vertex, stack);
  vertex->in_stack_bool = *num;


  p_cell curr = adj_list->listarray[vertex->id]->head;
  while(curr!=NULL){
    t_tarjan_vertex *w = &tarjan_list->vertices[curr->arrival-1];
    if (w->access_number == -1){
		parcours(w, num, stack, partition, adj_list, tarjan_list, id);
    vertex->access_number = MIN(vertex->access_number, w->access_number);
    }

    else if (w->in_stack_bool){
      vertex->access_number = MIN(vertex->access_number, w->number);
    }
    curr=curr->next;
  }

  if (vertex->access_number == vertex->number){
    int i=0;
    t_class * class = create_class(sizeof(tarjan_list->vertices[curr->arrival-1])/sizeof(t_tarjan_vertex));
    class->id = *id;
    id++;

    t_tarjan_vertex *w = pop(stack);
    w->in_stack_bool = 0;
    class->list->vertices[i]=*w;
    i++;

    while(w!=vertex){
      w = pop(stack);
      w->in_stack_bool = 0;
      class->list->vertices[i]=*w;
      i++;
    }
    partition->classes[i]=class;
  }
  return;
}

t_partition tarjan_algorithm(t_adjlist* adj_list){
  int * num=0;
  int * id=0;
  t_stack_tarjan * stack = create_empty_stack(adj_list->len);
  t_partition * partition = create_partition(adj_list->len);
  t_tarjan_list * tarjan_list = create_filled_tarjan_list(adj_list);
  for (int i = 0; i < adj_list->len; i++) {
    t_tarjan_vertex * vertex = &tarjan_list->vertices[i];
    parcours(vertex, num, stack, partition, adj_list, tarjan_list, id);
  }
  return *partition;
}

//void removeTransitiveLinks(t_link_array *p_link_array)
//{
//    int i = 0;
//    while (i < p_link_array->log_size)
//    {
//        t_link link1 = p_link_array->links[i];
//        int j = 0;
//        int to_remove = 0;
//        while (j < p_link_array->log_size && !to_remove)
//        {
//            if (j != i)
//            {
//                t_link link2 = p_link_array->links[j];
//                if (link1.from == link2.from)
//                {
//                    // look for a link from link2.to to link1.to
//                    int k = 0;
//                    while (k < p_link_array->log_size && !to_remove)
//                    {
//                        if (k != j && k != i)
//                        {
//                            t_link link3 = p_link_array->links[k];
//                            if ((link3.from == link2.to) && (link3.to == link1.to))
//                            {
//                                to_remove = 1;
//                            }
//                        }
//                        k++;
//                    }
//                }
//            }
//            j++;
//        }
//        if (to_remove)
//        {
//            // remove link1 by replacing it with the last link
//            p_link_array->links[i] = p_link_array->links[p_link_array->log_size - 1];
//            p_link_array->log_size--;
//        }
//        else
//        {
//            i++;
//        }
//    }
//}
