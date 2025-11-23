#include <stdio.h>
#include "chained.h"
#include "hasse.h"
#include "matrix.h"

int main() {

    printf("Let's initialize the graph using a text file form the data directory\n");
    p_adjlist new_adj = readGraph("../data/exemple3.txt");
    printf("\n");

    printf("Let's display the graph:\n");
    displayAdjList(*new_adj);
    printf("\n");

    printf("But is this matrix a Markov graph ? If not, why ?:\n");
    isMarkov(*new_adj);
    printf("\n");
    printf("Fine, now, create a file to display it in Mermaid:\n");
    drawGraph("../data/exemple3.txt");

    // Create the transitional matrix M of the graph
    p_mat thegmat = create_matrix(*test_adj);
    display_matrix(*thegmat);

    // // PART 3 OUT OF 3 TESTING AND VALIDATION
    // p_adjlist test_adj = createAdjList(5);
    // // for this example we use the same as in presented in the pdf
    // // 1 (effectively 0): sunny
    // addCell(test_adj->listarray[0], 0, (float) 0.34);
    // addCell(test_adj->listarray[0], 1, (float) 0.27);
    // addCell(test_adj->listarray[0], 3, (float) 0.18);
    // addCell(test_adj->listarray[0], 4, (float) 0.21);
    // // 2 (1) : cloudy
    // addCell(test_adj->listarray[1], 0, (float) 0.20);
    // addCell(test_adj->listarray[1], 1, (float) 0.40);
    // addCell(test_adj->listarray[1], 2, (float) 0.20);
    // addCell(test_adj->listarray[1], 4, (float) 0.20);
    // // 3 (2) : rain
    // addCell(test_adj->listarray[2], 1, (float) 0.41);
    // addCell(test_adj->listarray[2], 2, (float) 0.37);
    // addCell(test_adj->listarray[2], 3, (float) 0.09);
    // addCell(test_adj->listarray[2], 4, (float) 0.13);
    // // 4 (3) : storm
    // addCell(test_adj->listarray[3], 1, (float) 0.68);
    // addCell(test_adj->listarray[3], 2, (float) 0.20);
    // addCell(test_adj->listarray[3], 3, (float) 0.12);
    // // 5 (4) : sunny spells
    // addCell(test_adj->listarray[4], 0, (float) 0.12);
    // addCell(test_adj->listarray[4], 1, (float) 0.30);
    // addCell(test_adj->listarray[4], 4, (float) 0.58);
    //
    //
    // displayAdjList(*test_adj);
    //
    // // Create the transitional matrix M of the graph
    // p_mat thegmat = create_matrix(*test_adj);
    // display_matrix(*thegmat);
    //
    // // get M^3
    // p_mat m2 = mult_matrix(*thegmat, *thegmat);
    // p_mat m3 = mult_matrix(*thegmat, *m2);
    // printf("this is M^3 :\n");
    // display_matrix(*m3);
    // free_matrix(m2);
    // free_matrix(m3);
    // // get m^7
    // p_mat mn = zero_matrix(thegmat->len);
    // copy_matrix(*thegmat, mn);
    // for (int i = 0; i < 6; i++) {
    //     p_mat tocopythentofree = mult_matrix(*thegmat, *mn);
    //     copy_matrix(*tocopythentofree, mn);
    //     free_matrix(tocopythentofree);
    // }
    // printf("this is M^7 :\n");
    // display_matrix(*mn);
    // free_matrix(mn);
    //
    // // min value of n for which m^n - m^n-1 <= 0.01
    // float epsilon = 1;
    // int n = 1;
    // mn = zero_matrix(thegmat->len);
    // copy_matrix(*thegmat, mn);
    // while (epsilon > 0.01) {
    //     p_mat tocopythentofree = mult_matrix(*thegmat, *mn);
    //     epsilon = diff_matrix(*tocopythentofree, *mn);
    //     copy_matrix(*tocopythentofree, mn);
    //     free_matrix(tocopythentofree);
    //     n++;
    // }
    // printf("min value of n for which m^n - m^n-1 <= 0.01 :\n"
    //        "n = %d; epsilon = %f\n", n, epsilon);
    //
    // freeAdjList(test_adj);
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

    //TEST OF PART 2 III (théo)

    p_partition partoche = tarjan_algorithm(new_adj);
    p_mat MATRIXO = subMatrix(*thegmat,*partoche,2);
    display_matrix(*MATRIXO);

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
    printf("min value of n for which m^n - m^n-1 <= 0.01 :\n"
           "n = %d; epsilon = %f\n", n, epsilon);

    freeAdjList(test_adj);


    /// Test of the Part 2 of II
    /// creation of a Tarjan graph

    t_partition new_partition = tarjan_algorithm(new_adj);
    p_link_array plink = createTransitiveLinks(*new_adj, new_partition);
    removeTransitiveLinks(plink);
    graph_characteristics(new_partition, *plink);

   drawHasse(new_partition, *new_adj);
   displayAdjList(*new_adj);
   freeAdjList(new_adj);


    printf("\n----------Over.----------");
    return 0;
}
