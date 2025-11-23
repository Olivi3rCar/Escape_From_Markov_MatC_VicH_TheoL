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
	  tarjan_list->vertices[i].id = i+1;
   	tarjan_list->vertices[i].number = -1;
   	tarjan_list->vertices[i].access_number = -1;
    tarjan_list->vertices[i].in_stack_bool = 0;
    tarjan_list->list_l_len++;
  }

  return tarjan_list;
}

p_class link_vertex_to_class(t_adjlist vertices, t_partition part){
    // Allocate space for the linking array
    p_class linkedVC = (p_class) malloc(part.l_len * sizeof(t_class));
    for (int i = 0; i < part.l_len; i++) {
        // For each class in the partition
        for (int j = 0; j < part.classes[i]->len; j++) {
            // For each vertex in that class
            // We link the current vertex to the corresponding class
            // in the newly created array. (the index of the element of the array
            // corresponds to the id of the vertex)
            linkedVC[part.classes[i]->list->vertices[j].id] = *part.classes[i];
        }
    }
    return linkedVC;
}


p_link_array createTransitiveLinks(t_adjlist vertices, t_partition part){
    // Instantiation and allocation of the p_link_array
    p_link arrLLL = malloc(100 * sizeof(t_link));
    p_link_array linkA = malloc(sizeof(p_link_array));
    linkA->arr = arrLLL; linkA->len = 0;

    p_class linkedVC = link_vertex_to_class(vertices, part);
    for (int i = 0; i < vertices.len; i++) {
        // Ci is linkedVC[i]
        t_class Ci = linkedVC[i];
        // We instantiate through the adj clist of the vertex i
        p_cell curr = vertices.listarray[i]->head;
        while (curr != NULL) {
            // Curr is vertex j; Cj is linkedVC[j]
            t_class Cj = linkedVC[curr->arrival];
            int v = 1; int kk = 0;
            while (kk < linkA->len && v) {
                // for each link in the p_link_array
                // we check if the current link is already present
                t_link currelt = linkA->arr[kk++];
                if (Ci.id==linkedVC[currelt.from].id && Cj.id==linkedVC[currelt.to].id) {
                    v = 0;
                }
            }
            // if not already present, att link to linkarrayyyyyrfers
            if (v) {
                linkA->arr[linkA->len].from = Ci.id;
                linkA->arr[linkA->len].to = Cj.id;
                linkA->len++;
            }
            curr = curr->next;
        }
    }
    return linkA;
}


void graph_characteristics(t_partition partition, t_link_array links) {
    if (partition.l_len==1) {
        printf("The markov graph is irreducible\n");
        return;
    }

    for (int i = 0; i < partition.l_len; i++) {
        if (links.arr[i].to == i) {
            printf("\nClass %d {",i);
            for (int j = 0; j < partition.classes[i]->list->list_l_len-1; j++) {
                printf("%d,",partition.classes[i]->list->vertices[j].id);
            }
            printf("%d} is persistent. ",partition.classes[i]->list->vertices[partition.classes[i]->list->list_l_len-1].id);
            if (partition.classes[i]->len==1) {
                printf("The element inside is absorbing.");
            }

        }else {
            printf("\nClass %d {",i);
            for (int j = 0; j < partition.classes[i]->list->list_l_len-1; j++) {
                printf("%d,",partition.classes[i]->list->vertices[j].id);
            }
            printf("%d} is transient",partition.classes[i]->list->vertices[partition.classes[i]->list->list_l_len-1].id);
        }
    }
}


void removeTransitiveLinks(p_link_array linkArray)
{
    int i = 0;
    while (i < linkArray->log_size)
    {
        t_link link1 = linkArray->arr[i];
        int j = 0;
        int to_remove = 0;
        while (j < linkArray->log_size && !to_remove)
        {
            if (j != i)
            {
                t_link link2 = linkArray->arr[j];
                if (link1.from == link2.from)
                {
                    // look for a link from link2.to to link1.to
                    int k = 0;
                    while (k < linkArray->log_size && !to_remove)
                    {
                        if (k != j && k != i)
                        {
                            t_link link3 = linkArray->arr[k];
                            if (link3.from == link2.to && link3.to == link1.to)
                            {
                                to_remove = 1;
                            }
                        }
                        k++;
                    }
                }
            }
            j++;
        }
        if (to_remove)
        {
            // remove link1 by replacing it with the last link
            linkArray->arr[i] = linkArray->arr[linkArray->log_size - 1];
            linkArray->log_size--;
        }
        else
        {
            i++;
        }
    }
}

void freeTransitiveLinks(p_link_array linkArray){
    free(linkArray);
}

void drawHasse(t_partition part, t_adjlist graph) {

    FILE *output = fopen("../data/dusk.txt", "w");
    if (!output) {
        perror("Could not open/create the file for writing");
        exit(EXIT_FAILURE);
    }
    printf("1");
    fprintf(output, "---\n"
                    "config:\n"
                    "    layout: elk\n"
                    "    theme: neo\n"
                    "    look: neo\n"
                    "---\n\n"
                    "flowchart LR\n");

    ///Writing all the differents nodes
    for (int i = 0; i < part.l_len; i++) {
        fprintf(output, "%s[%d]\n",getID(i+1),part.classes[i]->id);
    }
    fprintf(output, "\n");

    printf("2");
    ///Linking the nodes
    p_link_array trLinks = createTransitiveLinks(graph, part);
    //     removeTransitiveLinks(trLinks);
    //     for (int i = 0; i < trLinks->len; i++){
    //         fprintf(output, "%s->%s\n",getID(trLinks->arr[i].from),getID(trLinks->arr[i].to));
    //         printf("huh ?\n%s->%s\n%d->%d\n",getID(trLinks->arr[i].from),getID(trLinks->arr[i].to),
    //                trLinks->arr[i].from,trLinks->arr[i].to);
    //     }

    printf("3");
    //freeTransitiveLinks(trLinks);

    printf("4");
    //fclose(output);
    printf("The file has been successfully output here: Escape_From_Markov_MatC_VicH_TheoL/data/dusk.txt\n");
}


t_class * create_class(const int edge_size) {
  t_class *new_class = (p_class)malloc(sizeof(t_class));
  if (!new_class) {
    printf("Memory allocation failed in create_class\n");
    exit(1);
  }

  new_class->list = malloc(sizeof(t_tarjan_list));
  if (!new_class->list) {
    printf("Memory allocation failed in create_class\n");
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

  new_class->list->list_l_len = 0;        /* current stored vertex count */
  new_class->list->list_p_len = edge_size;  /* max possible */

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
              t_partition* partition, t_adjlist* adj_list, t_tarjan_list* tarjan_list, int * id) {
  vertex->number = * num;

  printf("num : %d", * num);

  vertex->access_number = *num;

  (*num)++;

  push(vertex, stack);

  vertex->in_stack_bool = 1;

  printf("\ninnit\n");


  p_cell curr = adj_list->listarray[vertex->id-1]->head;
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

  if (vertex->access_number == vertex->number) {
    t_class *class = create_class(adj_list->len);
    printf("Class created\n");
    class->id = *id;
    (*id)++;

      t_tarjan_vertex *w = pop(stack);
      w->in_stack_bool = 0;
      class->list->vertices[class->list->list_l_len++] = *w;

    while (w != vertex) {
        w=pop(stack);
        w->in_stack_bool = 0;
        class->list->vertices[class->list->list_l_len++] = *w;

    }

      partition->classes[partition->l_len++] = class;

  }
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