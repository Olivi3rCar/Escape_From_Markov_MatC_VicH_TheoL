#include "hasse.h"

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

p_link_array createTransitiveLinks(t_partition part){
    // MATHIAS IL FAUT CREER UN TYPE QUI CONTIENT DEUX LINKS POUR LES LINKS LINKS THE SUN AAAAAH
    return;
}

void removeTransitiveLinks(p_link_array linkArray)
{
    int i = 0;
    while (i < linkArray->log_size)
    {
        t_link link1 = linkArray->links[i];
        int j = 0;
        int to_remove = 0;
        while (j < linkArray->log_size && !to_remove)
        {
            if (j != i)
            {
                t_link link2 = linkArray->links[j];
                if (link1.from == link2.from)
                {
                    // look for a link from link2.to to link1.to
                    int k = 0;
                    while (k < linkArray->log_size && !to_remove)
                    {
                        if (k != j && k != i)
                        {
                            t_link link3 = linkArray->links[k];
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
            p_link_array->links[i] = p_link_array->links[p_link_array->log_size - 1];
            p_link_array->log_size--;
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

    FILE *output = fopen("../data/dusk.txt", "w");
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
        fprintf(output, "%s[%s]\n",getID(i+1),part.classes[i].name);
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