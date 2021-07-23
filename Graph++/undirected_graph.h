#ifndef ORIENTED_GRAPH_H
#define ORIENTED_GRAPH_H

#include "graph.h"
#include <unordered_map>

//base class for graphs that use different data structures, graph is undirected
template<class node, typename weight_t = double>
class undirected_graph: public graph<node, weight_t>
{
private:
    //everything in private is for DSU, which is not available for directed graphs

    std::unordered_map<node*, node*> parent;
    std::unordered_map<node*, int> rank;

    void __create_set(node *n)
    {
        parent[n] = n;
        rank[n] = 1;
    }

    node* __get_set(node *n)
    {
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
        if (parent.find(n) == parent.end())
            __create_set(n);
    }

    //checks if the graph contains given node
    bool contains(node *n) override
    {
        return parent.find(n) != parent.end();
    }

    //connects two nodes according to graph's orientation
    //if the weight is not specified connects two nodes with a default-weighted edge
    //if graph doesn't contain at least one node from the arguments returns false
    //else returns true and connects two nodes if they weren't connected earlier
    //or reconnects two nodes with a new edge that has new weight
    bool connect(node *a, node *b) override
    {
        auto f1 = parent.find(a), f2 = parent.find(b);
        if (f1 == parent.end() || f2 == parent.end())
            return false;
        if (__get_set(a) != __get_set(b))
            __union_sets(a, b);
        return true;
    }

    //disconnects two nodes according to graph's orientation
    //in case of directed graph deletes a directed edge from first to second parameter
    //else just deletes the edge between two nodes if it exists
    //still returns true if the nodes weren't connected
    //returns false if two nodes are not in graph
    bool disconnect(node *a, node *b) override
    {

    }

    //TODO: search for a way to optimize

    //finds the pointer to object that points to the object that equals the argument
    //if the objects in graph are not unique there's no guarantee the method will return
    //the pointer you expected, use find_all instead to find all the occurrences
    node* find(const node &n) override
    {
        for (auto it = parent.begin(); it != parent.end(); ++it)
            if (*(it->first) == n)
                return it->first;
        return nullptr;
    }

    //finds all the pointers to objects that point to the objects that equal the argument
    //writes all the found pointers to destination container (either vector or list)
    //d_first is the iterator to beginning of the sequence
    void find_all(const node &n, typename std::vector<node*>::iterator d_first) override
    {
        for (auto it = parent.begin(); it != parent.end(); ++it)
        {
            if (*(it->first) == n)
                *(d_first++) = it->first;
        }
    }

    void find_all(const node &n, typename std::list<node*>::iterator d_first) override
    {
        for (auto it = parent.begin(); it != parent.end(); ++it)
        {
            if (*(it->first) == n)
                *(d_first++) = it->first;
        }
    }
};

#endif // ORIENTED_GRAPH_H
