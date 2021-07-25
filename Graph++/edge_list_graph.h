#ifndef EDGE_LIST_GRAPH_H
#define EDGE_LIST_GRAPH_H

#include "graph.h"

template<class node, typename weight_t = double>
class edge_list_graph: virtual public graph<node, weight_t>
{

};

#endif // EDGE_LIST_GRAPH_H
