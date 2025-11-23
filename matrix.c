//
// Created by carva on 22/11/2025.
//

#include "matrix.h"

p_mat create_matrix(t_adjlist graph){
    // First, allocation of the matrix
    float ** newmat = (float **) malloc(graph.len * sizeof(float*));
    // Then, for each vertex in the adjacency list
    for (int i = 0; i < graph.len; i++) {
        // Allocation of the corresponding array in the matrix,
        // use calloc for declaration of elements at 0
        newmat[i] = (float*) calloc(graph.len,sizeof(float));
        // then we go through the edges to fill this array
        p_cell curr = graph.listarray[i]->head;
        while (curr != NULL) {
            newmat[i][curr->arrival] = curr->proba;
            curr = curr->next;
        }
    }
    p_mat gmat = (p_mat) malloc(sizeof(t_mat));
    gmat->mat = newmat; gmat->len = graph.len;
    return gmat;
}


p_mat zero_matrix(int len){
    // First, allocation of the matrix
    float ** newmat = (float **) malloc(len * sizeof(float*));
    for (int i = 0; i < len; i++) {
        // use calloc for declaration of elements at 0
        newmat[i] = (float*) calloc(len,sizeof(float));
    }
    p_mat gmat = (p_mat) malloc(sizeof(t_mat));
    gmat->mat = newmat; gmat->len = len;
    return gmat;
}

void display_matrix(t_mat gmat){
    for(int i = 0; i < gmat.len; i++){
        for(int j = 0; j < gmat.len; j++) {
            printf("%.3f\t", gmat.mat[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(p_mat tofree){
    for (int i = 0; i < tofree->len; i++) {
        free(tofree->mat[i]);
    }
    free(tofree->mat);
    free(tofree);
}

void copy_matrix(t_mat from, p_mat to){
    // first check if all is good my man
    if (from.len != to->len) {
        // you serious ?
        printf("Error : two matrices not of the same size. Returning.");
        return;
    }
    //all is good, we copy
    for (int i = 0; i < from.len; i++) {
        for (int j = 0; j < from.len; j++) {
            to->mat[i][j] = from.mat[i][j];
        }
    }
}

p_mat mult_matrix(t_mat mat1, t_mat mat2){
    // first check if all is good my dude
    if (mat1.len != mat2.len) {
        // you serious ?
        printf("Error : two matrices not of the same size. Returning.");
        return NULL;
    }
    // instantiation of the matrix to output
    p_mat newmat = zero_matrix(mat1.len);
    // filling the matrix
    for (int i = 0; i < mat1.len; i++) {
        for (int j = 0; j < mat1.len; j++) {
            for (int k = 0; k < mat1.len; k++) {
                // formula of matrix multiplication
                newmat->mat[i][j] += mat1.mat[i][k]*mat2.mat[k][j];
            }
        }
    }
    return newmat;
}


float diff_matrix(t_mat mat1, t_mat mat2){
    float final = 0;
    // first check if all is good my bro
    if (mat1.len != mat2.len) {
        // you serious ?
        printf("Error : two matrices not of the same size. Returning.");
        return 0;
    }
    for (int i = 0; i < mat1.len; i++) {for (int j = 0; j < mat1.len; j++){
        float sum = mat1.mat[i][j] - mat2.mat[i][j];
        if (sum < 0) {final -= sum;} else {final += sum;}
    }}
    return final;
}

p_mat subMatrix(t_mat matrix, t_partition part, int compo_index) {
    //We look for the size of our new Submat
    int subMat_size = part.classes[compo_index]->len;
    //we create our new subMat of the size subMat_size
    t_mat * Submat = zero_matrix(subMat_size);
    //We get the values of the classes to get the values out of matrix (red pill)
    int * class =(int*)malloc(subMat_size * sizeof(int));
    for (int j = 0; j < part.classes[compo_index]->list->list_l_len-1; j++) {
        class[j]=part.classes[compo_index]->list->vertices[j].id;
    }
    //Now we can get the values out of matrix and put them into Submat
    for (int i = 0; i < subMat_size; i++) {
        for (int j = 0; j < subMat_size; j++) {
            Submat->mat[i][j] = matrix.mat[class[i]][class[j]];
        }
    }
    return Submat;
}