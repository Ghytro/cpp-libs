#ifndef UNDIRECTED_ADJACENCY_MATRIX_GRAPH_H
#define UNDIRECTED_ADJACENCY_MATRIX_GRAPH_H

#include "undirected_graph.h"
#include "adjacency_matrix_graph.h"

template<class node, typename weight_t = double>
class undirected_adjacency_matrix_graph: public undirected_graph<node, weight_t>, public adjacency_matrix_graph<node, weight_t>
{
    typedef undirected_graph<node, weight_t> undir_g;
    typedef adjacency_matrix_graph<node, weight_t> am_g;
};

#endif // UNDIRECTED_ADJACENCY_MATRIX_GRAPH_H
