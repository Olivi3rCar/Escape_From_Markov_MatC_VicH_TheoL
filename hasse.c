#include "hasse.h"

t_tarjan_list * create_filled_tarjan_list(const t_adjlist * adj_list){
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


  tarjan_list->list_l_len = 0;

  for(int i = 0; i < adj_list->len; i++){
	  tarjan_list->vertices[i].id = i;
   	tarjan_list->vertices[i].number = -1;
   	tarjan_list->vertices[i].access_number = -1;
    tarjan_list->vertices[i].in_stack_bool = 0;
    tarjan_list->list_l_len++;
  }

  return tarjan_list;
}


t_class * create_class(const int edge_size) {
  t_class *new_class = malloc(sizeof *new_class);
  if (!new_class) {
    printf("Memory allocation failed in create_partition\n");
    exit(1);
  }

  new_class->list = malloc(sizeof *new_class->list);
  if (!new_class->list) {
    printf("Memory allocation failed in create_partition\n");
    free(new_class);
    exit(1);
  }

  new_class->list->vertices = calloc((size_t)edge_size, sizeof *new_class->list->vertices);
  if (!new_class->list->vertices) {
    printf("Memory allocation failed in create_partition\n");
    free(new_class->list);
    free(new_class);
    exit(1);
  }

  new_class->len = edge_size;
  return new_class;
}


t_partition * create_partition(const int len){
  t_partition * new_partition = malloc(sizeof(t_partition));
  new_partition->classes = malloc(len*sizeof(t_class*));
  if(new_partition->classes == NULL){
    printf("Memory allocation failed in create_partition\n");
    exit(1);
  }
  new_partition->p_len = len;
  new_partition->l_len =0;
  return new_partition;
}

t_stack_cell* create_cell_stack (){
  t_stack_cell* cell = malloc(sizeof(t_stack_cell));
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
  t_stack_cell * new_cell = create_cell_stack();
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
  if (stack->logical_size == 0) {
    printf("Stack is empty\n");
    return NULL;
  }
  t_stack_cell *cell = stack->top;
  t_tarjan_vertex * vertex = stack->top->cell;
  stack->top=stack->top->next;
  stack->logical_size--;
  free(cell);
  return vertex;
}

void parcours(t_tarjan_vertex * vertex, int *num, t_stack_tarjan* stack,
              t_partition* partition, t_adjlist* adj_list, t_tarjan_list* tarjan_list, int * id){

  vertex->number = * num;

  printf("num : %d", * num);

  vertex->access_number = *num;

  (*num)++;

  push(vertex, stack);

  vertex->in_stack_bool = 1;

  printf("\ninnit\n");


  p_cell curr = adj_list->listarray[vertex->id]->head;
  while(curr!=NULL){
    printf("Inside a while loop...\n");
    t_tarjan_vertex *w = &tarjan_list->vertices[curr->arrival-1];
    if (w->access_number == -1){
      printf("/!\\ Another parcours begins\n\n");
		  parcours(w, num, stack, partition, adj_list, tarjan_list, id);
      printf("/?\\Exiting a parcours\n\n");
      vertex->access_number = MIN(vertex->access_number, w->access_number);
    }

    else if (w->in_stack_bool){
      vertex->access_number = MIN(vertex->access_number, w->number);
    }
    curr=curr->next;
  }
  printf("Went through the while loop\n\n");

  if (vertex->access_number == vertex->number){
    int i=0;
    t_class * class = create_class(adj_list->len);
    printf("Class created\n");
    class->id = * id;
    (*id)++;

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
    partition->classes[partition->l_len]=class;
    partition->l_len++;
  }
  printf("Went through the if loop\n");
}

t_partition tarjan_algorithm(t_adjlist* adj_list){
  int num=0;
  int id=0;
  t_stack_tarjan * stack = create_empty_stack(adj_list->len);
  t_partition * partition = create_partition(adj_list->len);
  t_tarjan_list * tarjan_list = create_filled_tarjan_list(adj_list);
  printf("Beginning parcours function run\n");
  for (int i = 0; i < adj_list->len; i++) {
    t_tarjan_vertex * vertex = &tarjan_list->vertices[i];
    printf("Run number : %d\n",i+1);
    if (vertex->access_number == -1) {
      parcours(vertex, &num, stack, partition, adj_list, tarjan_list, &id);
    }
  }
  printf("I'm ... done ???");
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