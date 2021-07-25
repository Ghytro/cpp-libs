#ifndef UNDIRECTED_ADJACENCY_LIST_GRAPH_H
#define UNDIRECTED_ADJACENCY_LIST_GRAPH_H

#include "undirected_graph.h"
#include "adjacency_list_graph.h"

template<class node, typename weight_t = double>
class undirected_adjacency_list_graph: public undirected_graph<node, weight_t>, public adjacency_list_graph<node, weight_t>
{
    typedef undirected_graph<node, weight_t> undir_g;
    typedef adjacency_list_graph<node, weight_t> al_g;

public:
    undirected_adjacency_list_graph(weight_t default_edge_weight = static_cast<weight_t>(1)):
        undirected_graph<node, weight_t>(default_edge_weight){}

    void add_node(node *n) override
    {
        this->undir_g::add_node(n);
        this->al_g::add_node(n);
    }

    void remove_node(node *n) override
    {
        this->undir_g::remove_node(n);
        this->al_g::remove_node(n);
    }

    bool connect(node *a, node *b) override
    {
        if (!this->undir_g::connect(a, b))
            return false;
        return this->al_g::connect(a, b);
    }

    bool connect(node *a, node *b, weight_t weight) override
    {
        if (!this->undir_g::connect(a, b))
            return false;
        return this->al_g::connect(a, b, weight);
    }

    bool disconnect(node *a, node *b) override
    {
        if (!this->undir_g::disconnect(a, b))
            return false;
        return this->al_g::disconnect(a, b);
    }

    weight_t min_distance(node *from, node *to) override
    {
        if (!this->path_exists(from, to))
            throw path_not_found();
        return this->al_g::min_distance(from, to);
    }

    weight_t min_distance(node *from, node *to, typename std::vector<node*>::iterator d_first) override
    {
        if (!this->path_exists(from, to))
            throw path_not_found();
        return this->al_g::min_distance(from, to, d_first);
    }

    bool path_exists(node *from, node *to) override
    {
        return this->undir_g::path_exists(from, to);
    }
};

#endif // UNDIRECTED_ADJACENCY_LIST_GRAPH_H
