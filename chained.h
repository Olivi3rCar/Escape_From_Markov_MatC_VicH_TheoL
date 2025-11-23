//
// Created by carva on 20/10/2025.
//

#ifndef INC_2526_TI301_PJT_CHAINED_H
#define INC_2526_TI301_PJT_CHAINED_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/// s_cell is the base cell element for a linked list
///
/// \param arrival The index of the arrival node
/// \param proba The probability of going to arrival
/// \param next Pointer to the next s_cell in the list
struct s_cell{
    int arrival;
    float proba;
    struct s_cell* next;
};

/// t_cell is to be used for referencing a s_cell element,
/// p_cell for a pointer to such element
typedef struct s_cell t_cell, *p_cell;

/// s_clist is the base linked list type
///
/// \param head Pointer to the first cell of the list
struct s_clist{
    p_cell head;
};

/// t_clist is to be used for referencing a s_clist element,
/// p_clist for a pointer to such element
typedef struct s_clist t_clist, *p_clist;

/// s_adjlist is the base adjacency list regrouping clists
///
/// \param listarray Pointer to the first element of an array of clists
/// \param len The number of clists contained in listarray
struct s_adjlist{
    p_clist * listarray;
    int len;
};

/// t_adjlist is to be used for referencing a s_adjlist element,
/// p_adjlist for a pointer to such element
typedef struct s_adjlist t_adjlist, *p_adjlist;

/// Function to create and dynamically allocate a t_cell element
///
/// \param arrVer Value of the arrival Vertex of the cell
/// \param prob Probability of going to arrVer
/// \return Pointer to the newly created cell
p_cell createCell(int arrVer, float prob);

/// Function to create and dynamically allocate a t_clist element
///
/// \return Pointer to the newly created CList
p_clist createCList();

/// Function to add a new element to an existing CList
///
/// \param l Pointer to the CList to which we want to add an element
/// \param arrVer Value of the arrival Vertex of the cell
/// \param prob Probability of going to arrVer
void addCell(p_clist l, int arrVer, float prob);

/// Function to display a CList on the terminal
///
/// \param l Clist to display
void displayCList(t_clist l);

/// Function to free the space allocated to a CList
///
/// \param l Pointer to the CList to free
void freeCList(p_clist l);


/// Function to create and dynamically allocate a t_adjlist element
///
/// \param VictorCompliantnumberOfVertices number of vertices
/// the described graph should contain
/// \return Pointer to the newly allocated AdjList element
p_adjlist createAdjList(int VictorCompliantnumberOfVertices);

/// Function to display an AdjList on the terminal
///
/// \param a t_adjlist to display
void displayAdjList(t_adjlist a);

/// Function to free the space allocated to an AdjList
///
/// \param a Pointer to the AdjList to free
void freeAdjList(p_adjlist a);

char *getID(int i);

/// Checks if an adjacency list is a Markov Chain or not, and outputs what's wrong
void isMarkov(t_adjlist);

/// Reads a graph form a text file
/// @param filename
/// @return the list corresponding to the text
p_adjlist readGraph (const char * filename);

/// writes a text file to represent a graph, inputed via a text file too
/// @param filename
void drawGraph (const char * filename);


#endif //INC_2526_TI301_PJT_CHAINED_H
