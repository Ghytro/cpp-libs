#ifndef UNDIRECTED_EDGE_LIST_GRAPH_H
#define UNDIRECTED_EDGE_LIST_GRAPH_H

#include "undirected_graph.h"
#include "edge_list_graph.h"

template<class node, typename weight_t = double>
class undirected_adjacency_matrix_graph: public undirected_graph<node, weight_t>, public edge_list_graph<node, weight_t>
{
    typedef undirected_graph<node, weight_t> undir_g;
    typedef edge_list_graph<node, weight_t> el_g;
};

#endif // UNDIRECTED_EDGE_LIST_GRAPH_H
