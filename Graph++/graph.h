#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>

//base class, directed graph
template<class node, typename weight_t = double>
class graph
{
private:
    const weight_t __default_edge_weight;

protected:
    graph(weight_t default_edge_weight = static_cast<weight_t>(1)): __default_edge_weight(default_edge_weight){}

public:
    weight_t default_edge_weight() {return __default_edge_weight;}

    //adds new node to graph
    //if the graph already contains this node does nothing
    virtual void add_node(node*) = 0;

    //checks if the graph contains given node
    virtual bool contains(node*) = 0;

    //connects two nodes according to graph's orientation
    //if the weight is not specified connects two nodes with a default-weighted edge
    //if graph doesn't contain at least one node from the arguments returns false
    //else returns true and connects two nodes if they weren't connected earlier
    //or reconnects two nodes with a new edge that has new weight
    virtual bool connect(node*, node*) = 0;
    virtual bool connect(node*, node*, weight_t) = 0;

    //disconnects two nodes according to graph's orientation
    //in case of directed graph deletes a directed edge from first to second parameter
    //else just deletes the edge between two nodes if it exists
    //still returns true if the nodes weren't connected
    //returns false if two nodes are not in graph
    virtual bool disconnect(node*, node*) = 0;

    //finds the pointer to object that points to the object that equals the argument
    //if the objects in graph are not unique there's no guarantee the method will return
    //the pointer you expected, use find_all instead to find all the occurrences
    virtual node* find(const node&) = 0;

    //finds all the pointers to objects that point to the objects that equal the argument
    //writes all the found pointers to destination container (either vector or list)
    //d_first is the iterator to beginning of the sequence
    virtual void find_all(const node&, typename std::vector<node*>::iterator d_first) = 0;
    virtual void find_all(const node&, typename std::list<node*>::iterator d_first) = 0;

    //calculates minimal distance between two given nodes using Dijkstra's algorithm
    //won't work if the graph contains edges with negative weight
    //the weight of the path is the return value of the method
    //the method can also write found path to either vector or list of pointers
    //d_first is the iterator to beginning of the sequence
    virtual weight_t min_distance(node *from, node *to) = 0;
    virtual weight_t min_distance(node *from, node *to, typename std::vector<node*>::iterator d_first) = 0;
    virtual weight_t min_distance(node *from, node *to, typename std::list<node*>::iterator d_first) = 0;

    //calculates weight of a given path, which is given in either a list or vector of pointers to objects contained in graph
    //if it's unable to count the given path (in case graph contains not all the nodes) or the path doesn't exist returns -1
    virtual weight_t path_weight(typename std::vector<node*>::iterator first, typename std::vector<node*>::iterator last) = 0;
    virtual weight_t path_weight(typename std::list<node*>::iterator first, typename std::list<node*>::iterator last) = 0;
    virtual weight_t path_weight(node *first, node *last) = 0; //pointers are for c-style array

    //check if the path between two nodes
    //exists without calculating the minimal path
    //in case of directed graph checks the path existence
    //using bfs, in case of undirected graph uses DSU
    //to speed up the operation to approximately time-constant
    virtual bool path_exists(node *from, node *to) = 0;
};

#endif // GRAPH_H
