#include <stdio.h>
#include "chained.h"
#include "hasse.h"
#include "matrix.h"

int main() {
    ///Part 1 validations
    ///Validation of step 1
    printf("Let's initialize the graph using a text file form the data directory\n");
    p_adjlist new_adj = readGraph("../data/exemple3.txt");
    printf("\n");

    printf("Let's display the graph:\n");
    displayAdjList(*new_adj);
    printf("\n");


    ///Validation of step 2
    printf("But is this matrix a Markov graph ? If not, why ?:\n");
    isMarkov(*new_adj);
    printf("\n");


    ///Validation of step 3
    printf("Fine, now, create a file to display it in Mermaid:\n");
    drawGraph("../data/exemple3.txt");





    ///Part 2 validations
    //Validation of step 1
    p_partition new_partition = tarjan_algorithm(new_adj);
    printf("\nThis is the partition we get from example 3:\n");
    display_tarjan(*new_partition);

    //Validation of step 2
    drawHasse(*new_partition, *new_adj);

    //Validation of step 3
    p_link_array plink = createTransitiveLinks(*new_adj, *new_partition);
    graph_characteristics(*new_partition, *plink);
    printf("\n\n");





    ///Part 3 validations
    //Validation of step 1
    p_adjlist mat_adj = readGraph("../data/exemple_meteo.txt");
    p_adjlist mat_adj1 = readGraph("../data/exemple1.txt");
    p_adjlist mat_adj2 = readGraph("../data/exemple2.txt");
    p_adjlist mat_adj3= readGraph("../data/exemple3.txt");


   // Create the transitional matrix M of the graph
   p_mat thegmat = create_matrix(*mat_adj);
    p_mat thegmat1 = create_matrix(*mat_adj1);
    p_mat thegmat2 = create_matrix(*mat_adj2);
    p_mat thegmat3 = create_matrix(*mat_adj3);



   // get M^3
   p_mat m2 = mult_matrix(*thegmat, *thegmat);
   p_mat m3 = mult_matrix(*thegmat, *m2);
   printf("this is M^3 :\n");
   display_matrix(*m3);
   free_matrix(m2);
   free_matrix(m3);
   // get m^7
   p_mat mn = zero_matrix(thegmat->len);
   copy_matrix(*thegmat, mn);
   for (int i = 0; i < 6; i++) {
       p_mat tocopythentofree = mult_matrix(*thegmat, *mn);
       copy_matrix(*tocopythentofree, mn);
       free_matrix(tocopythentofree);
   }
   printf("this is M^7 :\n");
   display_matrix(*mn);
   free_matrix(mn);

   // min value of n for which m^n - m^n-1 <= 0.01
   float epsilon = 1;
   int n = 1;
   mn = zero_matrix(thegmat->len);
   copy_matrix(*thegmat, mn);
   while (epsilon > 0.01) {
       p_mat tocopythentofree = mult_matrix(*thegmat, *mn);
       epsilon = diff_matrix(*tocopythentofree, *mn);
       copy_matrix(*tocopythentofree, mn);
       free_matrix(tocopythentofree);
       n++;
   }
   printf("\nFor example meteo :\nmin value of n for which m^n - m^n-1 <= 0.01 :\n"
          "n = %d; epsilon = %f\n\n", n, epsilon);

    // min value of n for which m^n - m^n-1 <= 0.01
    epsilon = 1;
    n = 1;
    mn = zero_matrix(thegmat1->len);
    copy_matrix(*thegmat1, mn);
    while (epsilon > 0.01) {
        p_mat tocopythentofree = mult_matrix(*thegmat1, *mn);
        epsilon = diff_matrix(*tocopythentofree, *mn);
        copy_matrix(*tocopythentofree, mn);
        free_matrix(tocopythentofree);
        n++;
    }
    printf("For the file Example 1 :\nmin value of n for which m^n - m^n-1 <= 0.01 :\n"
           "n = %d; epsilon = %f\n\n", n, epsilon);

    // min value of n for which m^n - m^n-1 <= 0.01
    epsilon = 1;
    n = 1;
    mn = zero_matrix(thegmat2->len);
    copy_matrix(*thegmat2, mn);
    while (epsilon > 0.01) {
        p_mat tocopythentofree = mult_matrix(*thegmat2, *mn);
        epsilon = diff_matrix(*tocopythentofree, *mn);
        copy_matrix(*tocopythentofree, mn);
        free_matrix(tocopythentofree);
        n++;
    }
    printf("For the file Example 2 :\nmin value of n for which m^n - m^n-1 <= 0.01 :\n"
           "n = %d; epsilon = %f\n\n", n, epsilon);

    // min value of n for which m^n - m^n-1 <= 0.01
    epsilon = 1;
    n = 1;
    mn = zero_matrix(thegmat3->len);
    copy_matrix(*thegmat3, mn);
    while (epsilon > 0.01 && n<10000) {
        p_mat tocopythentofree = mult_matrix(*thegmat3, *mn);
        epsilon = diff_matrix(*tocopythentofree, *mn);
        copy_matrix(*tocopythentofree, mn);
        free_matrix(tocopythentofree);
        n++;
    }
    printf("For the file Example 3, we have an infinite loop, because example 3 isn't a markov graph");
    printf("For the file Example 3 :\nmin value of n for which m^n - m^n-1 <= 0.01 :\n"
       "n = %d; epsilon = %f\n\n", n, epsilon);

    display_matrix(*thegmat2);
    p_partition meteo_partition_cest_quand_meme_un_peu_drole = tarjan_algorithm(mat_adj2);
    p_link_array kasame_teo = createTransitiveLinks(*mat_adj2, *meteo_partition_cest_quand_meme_un_peu_drole);
    graph_characteristics(*meteo_partition_cest_quand_meme_un_peu_drole, *kasame_teo);
    for (int i=0; i<meteo_partition_cest_quand_meme_un_peu_drole->l_len;i++) {
        p_mat sub2 = subMatrix(*thegmat2, *meteo_partition_cest_quand_meme_un_peu_drole, i);
        printf("\n\nThis is the submatrix for class %d:\n",i+1);
        display_matrix(*sub2);
    }
    p_mat sub2 = subMatrix(*thegmat2, *meteo_partition_cest_quand_meme_un_peu_drole, 1);

    mn = zero_matrix(sub2->len);
    copy_matrix(*sub2, mn);
    for (int i = 0; i < 300; i++) {
        p_mat tocopythentofree = mult_matrix(*sub2, *mn);
        copy_matrix(*tocopythentofree, mn);
        free_matrix(tocopythentofree);
    }
    printf("\nThis is the stationnary matrix of the 2nd class sub matrix of the example 2\n");
    display_matrix(*mn);

    return 0;
}