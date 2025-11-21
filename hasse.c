#include "hasse.h"

t_tarjan_list * create_tarjan_list(t_adjlist * adj_list){
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

t_stack_cell* create_cell_stack (t_stack_tarjan * stack){
  t_stack_cell* cell = (t_stack_cell*) malloc(sizeof(t_stack_cell));
  if(cell == NULL){
    printf("Memory allocation failed in stack_create_cell\n");
    exit(1);
  }
  return cell;
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

void parcours(t_tarjan_vertex * vertex, int *num, t_stack_tarjan* stack,
              t_partition* partition, t_adjlist* adj_list, t_tarjan_list* tarjan_list){
  vertex->number = *num;
  vertex->access_number = *num;
  num++;
  push(vertex, stack);
  vertex->in_stack_bool = *num;

  //We're going to use the adj_list to get all the successors to the vertex.
  p_cell curr = adj_list->listarray[vertex->id]->head;
  while(curr!=NULL){
    t_tarjan_vertex *w = &tarjan_list->vertices[curr->arrival-1];
    if (w->access_number == -1){
		parcours(w, num, stack, partition, adj_list, tarjan_list);
        vertex->access_number = MIN(vertex->access_number, w->access_number);
    }else if (w->in_stack_bool){
      vertex->access_number = MIN(vertex->access_number, w->number);
    }
    curr=curr->next;
  }
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
