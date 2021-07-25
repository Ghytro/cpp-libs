#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "graph.h"

template<class node, typename weight_t = double>
class adjacency_matrix_graph: virtual public graph<node, weight_t>
{

};

#endif // ADJACENCY_MATRIX_GRAPH_H
