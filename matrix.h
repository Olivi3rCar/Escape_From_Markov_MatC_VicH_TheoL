//
// Created by carva on 22/11/2025.
//

#ifndef INC_2526_TI301_PJT_MATRIX_H
#define INC_2526_TI301_PJT_MATRIX_H

#include "chained.h"
#include "hasse.h"

typedef struct s_mat{
    float ** mat; int len;
}t_mat, *p_mat;

/// Function that, for a Markov graph,
/// creates the associated transitional probability matrix
/// \param graph the adjacency list representing all vertices of the graph
/// \return The newly created matrix
p_mat create_matrix(t_adjlist graph);

/// Function to instantiate a matrix filled with zeros
p_mat zero_matrix(int len);

/// Dynamically frees the matrix passed in argument
/// \param tofree the matrix to free
void free_matrix(p_mat tofree);

/// Function to display transitional probability matrix of a graph
/// \param gmat transitional probability matrix of a graph
void display_matrix(t_mat gmat);

/// Function to copy values from a matrix to another of same size
/// \param from matrix to copy values from
/// \param to matrix to copy values to
void copy_matrix(t_mat from, p_mat to);

/// Function that outputs the product of 2 matrices
/// \param mat1 left matrix
/// \param mat2 right matrix
/// \return the matrix produced by the result
p_mat mult_matrix(t_mat mat1, t_mat mat2);

/// Function that calculate the absolute difference between two matrices
/// \param mat1 first matrix
/// \param mat2 second matrix
/// \return the absolute difference between mat1 & mat2
float diff_matrix(t_mat mat1, t_mat mat2);

p_mat subMatrix(t_mat matrix, t_partition part, int compo_index);

#endif //INC_2526_TI301_PJT_MATRIX_H
