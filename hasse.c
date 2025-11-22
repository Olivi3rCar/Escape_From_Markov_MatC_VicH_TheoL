#include "hasse.h"
#include "chained.h"

p_tarjan_list create_tarjan_list(t_adjlist * adj_list){
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

  for (int i = 0; i < adj_list->len; i++) {
     tarjan_list->vertices[i].id = i;
     tarjan_list->vertices[i].number = -1;
     tarjan_list->vertices[i].access = -1;
     tarjan_list->vertices[i].bool = 0;
  }

  return tarjan_list;
}

p_class link_vertex_to_class(t_adjlist vertices, t_partition part){
    // Allocate space for the linking arrat
    p_class linkedVC = (p_class) malloc(vertices.len * sizeof(t_class) );
    for (int i = 0; i < part.len; i++) {
        // For each class in the partition
        for (int j = 0; j < part.classes[i].len; i++) {
            // For each vertex in that class
            // We link the current vertex to the corresponding class
            // in the newly created array. (the index of the element of the array
            // corresponds to the id of the vertex)
            linkedVC[part.classes[i].vertices[j].id] = part.classes[i];
        }
    }
    return linkedVC;
}

p_link_array createTransitiveLinks(t_adjlist vertices, t_partition part){
    // Instantiation and allocation of the p_link_array
    p_link arrLLL = (p_link) malloc(567 * sizeof(t_link));
    p_link_array linkA = (p_link_array) malloc(sizeof(p_link_array));
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
                t_link currelt = linkA->arr[kk];
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
        }
    }
    return linkA;
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
                            if ((link3.from == link2.to) && (link3.to == link1.to))
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
            linkArray->arr[i] =  linkArray->arr[ linkArray->log_size - 1];
             linkArray->log_size--;
        }
        else
        {
            i++;
        }
    }
}

void freeTransitiveLinks(p_link_array linkArray){
    return;
}

void drawHasse(t_partition part) {

    FILE *output = fopen("../data/exemple_hasse1.txt", "w");
    if (!output) {
        perror("Could not open/create the file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(output, "---\n"
                    "config:\n"
                    "    layout: elk\n"
                    "    theme: neo\n"
                    "    look: neo\n"
                    "---\n\n"
                    "flowchart LR\n");

    ///Writing all the differents nodes
    for (int i = 0; i < part.len; i++) {
        fprintf(output, "%s[%s]\n",getID(i+1),part.classes[i].id);
    }
    fprintf(output, "\n");

    ///Linking the nodes
    //p_link_array trLinks = createTransitiveLinks();
    //removeTransitiveLinks(trLinks);
    //for (truc) {machin dans output}

    fclose(output);
    printf("The file has been successfully outputed here: Escape_From_Markov_MatC_VicH_TheoL/data/ariel.txt\n");
    return;
}