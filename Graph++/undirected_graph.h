#ifndef ORIENTED_GRAPH_H
#define ORIENTED_GRAPH_H

#include "graph.h"
#include <unordered_map>

//base class for graphs that use different data structures, graph is undirected
template<class node, typename weight_t = double>
class undirected_graph: virtual public graph<node, weight_t>
{
private:
    //everything in private is for DSU, which is not available for directed graphs

    std::unordered_map<node*, node*> parent;
    std::unordered_map<node*, int> rank;

    void __create_set(node *n)
    {
        parent.emplace(n, n);
        rank.emplace(n, 1);
    }

    node* __get_set(node *n)
    {
        if (parent.find(n) == parent.end())
            throw node_not_found();
        if (parent[n] == n)
            return n;
        return parent[n] = __get_set(parent[n]);
    }

    void __union_sets(node *a, node *b)
    {
        a = __get_set(a);
        b = __get_set(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
            {
                parent[a] = b;
                rank[b] += rank[a];
            }
            else
            {
                parent[b] = a;
                rank[a] += rank[b];
            }
        }
    }

protected:
    undirected_graph(weight_t default_edge_weight = static_cast<weight_t>(1)): graph<node, weight_t>(default_edge_weight){}

public:

    //adds new node to graph
    //if the graph already contains this node does nothing
    void add_node(node *n) override
    {
        __create_set(n);
    }

    //removes given node from graph
    //if graph doesn't contain this node does nothing
    void remove_node(node *n) override
    {

    }

    //connects two nodes according to graph's orientation
    //if the weight is not specified connects two nodes with a default-weighted edge
    //if graph doesn't contain at least one node from the arguments returns false
    //else returns true and connects two nodes if they weren't connected earlier
    //or reconnects two nodes with a new edge that has new weight
    bool connect(node *a, node *b) override
    {
        try
        {
            __union_sets(a, b);
        }
        catch (const node_not_found&)
        {
            return false;
        }
        return true;
    }

    //disconnects two nodes according to graph's orientation
    //in case of directed graph deletes a directed edge from first to second parameter
    //else just deletes the edge between two nodes if it exists
    //still returns true if the nodes weren't connected
    //returns false if two nodes are not in graph
    bool disconnect(node *a, node *b) override
    {

        return true;
    }

    bool path_exists(node *a, node *b) override
    {
        try
        {
            return __get_set(a) == __get_set(b);
        }
        catch (const node_not_found&)
        {
            return false;
        }
    }
};

#endif // ORIENTED_GRAPH_H
