#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdio.h>

void isMarkov(adjency_list);
adjacency_list readGraph (const char * filename);

void drawGraph (const char * filename, adjacency_list graph);
#endif