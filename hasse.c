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

  for (int i = 0; i < adj_list->len; i++) {
     tarjan_list->vertices[i].id = i;
     tarjan_list->vertices[i].number = -1;
     tarjan_list->vertices[i].access = -1;
     tarjan_list->vertices[i].bool = 0;
  }

  return tarjan_list;
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
