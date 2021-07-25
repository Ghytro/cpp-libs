#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "graph.h"
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>

template<class node, typename weight_t = double>
class adjacency_list_graph: virtual public graph<node, weight_t>
{
private:
    std::unordered_map<node*, std::unordered_map<node*, weight_t>> __adjacency_list;

    weight_t __count_min_distance(node *from, node *to, std::stack<node*> *path_stack = nullptr)
    {
        if (!this->contains(from) || !this->contains(to))
            throw path_not_found();
        std::unordered_map<node*, std::pair<weight_t, bool>> distances; //.first - total weight, .second - if the answer is found
        std::unordered_map<node*, node*> parents; //first - node; second - her parent
        node *current = from;
        distances.emplace(from, std::make_pair(0, true));

        while (current != to)
        {
            auto f = __adjacency_list.find(current);
            auto f_d = distances.find(current);
            f_d->second.second = true;
            for (auto it = f->second.cbegin(); it != f->second.cend(); ++it)
            {
                auto f_it_first = distances.find(it->first);
                if (f_it_first == distances.end())
                {
                    distances.emplace(it->first, std::make_pair(f_d->second.first + it->second, false));
                    if (path_stack != nullptr)
                        parents[it->first] = current;
                }
                else if (f_it_first->second.first > f_d->second.first + it->second)
                {
                    f_it_first->second.first = f_d->second.first + it->second;
                    if (path_stack != nullptr)
                        parents[it->first] = current;
                }
            }
            bool min_found = false;
            weight_t min_w;
            node *min_n = nullptr;
            for (auto it = distances.begin(); it != distances.end(); ++it)
            {
                if (!it->second.second && (!min_found || it->second.first < min_w))
                {
                    min_n = it->first;
                    min_w = it->second.first;
                    min_found = true;
                }
            }
            if (!min_found)
                throw path_not_found();
            current = min_n;
        }

        if (path_stack != nullptr)
        {
            path_stack->push(to);
            while (path_stack->top() != from)
                path_stack->push(parents[path_stack->top()]);
        }

        return distances[to].first;
    }

    template<class Iterator>
    void __answer_from_stack(std::stack<node*> &s_path, Iterator d_first)
    {
        while (!s_path.empty())
        {
            *(d_first++) = s_path.top();
            s_path.pop();
        }
    }

public:
    adjacency_list_graph(weight_t default_edge_weight = static_cast<weight_t>(1)): graph<node, weight_t>(default_edge_weight){}

    //adds new node to graph
    //if the graph already contains this node does nothing
    void add_node(node *n) override
    {
        __adjacency_list.emplace(n, std::unordered_map<node*, weight_t>());
    }

    //removes a node from graph
    //if graph didn't contain given node does nothing
    void remove_node(node *n) override
    {
        if (__adjacency_list.find(n) == __adjacency_list.end())
            return;
        //deleting all the edges going from given node
        __adjacency_list.erase(n);
        //deleting all edges coming to the given node
        for (auto it = __adjacency_list.begin(); it != __adjacency_list.end(); ++it)
            it->second.erase(n);
    }

    //checks if the graph contains given node
    bool contains(node *n) override
    {
        return __adjacency_list.find(n) != __adjacency_list.end();
    }

    //connects two nodes according to graph's orientation
    //if the weight is not specified connects two nodes with a default-weighted edge
    //if graph doesn't contain at least one node from the arguments returns false
    //else returns true and connects two nodes if they weren't connected earlier
    //or reconnects two nodes with a new edge that has new weight
    bool connect(node *from, node *to) override
    {
        auto f1 = __adjacency_list.find(from), f2 = __adjacency_list.find(to);
        if (f1 == __adjacency_list.end() || f2 == __adjacency_list.end())
            return false;
        f1->second.emplace(to, this->default_edge_weight());
        return true;
    }

    bool connect(node *from, node *to, weight_t weight) override
    {
        auto f1 = __adjacency_list.find(from), f2 = __adjacency_list.find(to);
        if (f1 == __adjacency_list.end() || f2 == __adjacency_list.end())
            return false;
        f1->second.emplace(to, weight);
        return true;
    }

    //disconnects two nodes according to graph's orientation
    //in case of directed graph deletes a directed edge from first to second parameter
    //else just deletes the edge between two nodes if it exists
    //still returns true if the nodes weren't connected
    //returns false if two nodes are not in graph
    bool disconnect(node *from, node *to) override
    {
        auto f1 = __adjacency_list.find(from), f2 = __adjacency_list.find(to);
        if (f1 == __adjacency_list.end() || f2 == __adjacency_list.end())
            return false;
        f1->second.erase(to);
        return true;
    }

    //finds the pointer to object that points to the object that equals the argument
    //if the objects in graph are not unique there's no guarantee the method will return
    //the pointer you expected, use find_all instead to find all the occurrences
    node* find(const node &n) override
    {
//        for (auto it = __adjacency_list.begin(); it != __adjacency_list.end(); ++it)
//            if (*(it->first) == n)
//                return it->first;
//        throw node_not_found();
        return nullptr;
    }

    //finds all the pointers to objects that point to the objects that equal the argument
    //writes all the found pointers to destination container (either vector or list)
    //d_first is the iterator to beginning of the sequence
    void find_all(const node &n, typename std::vector<node*>::iterator d_first) override
    {
//        for (auto it = __adjacency_list.begin(); it != __adjacency_list.end(); ++it)
//            if (*(it->first) == n)
//                *(d_first++) = it->first;
    }

    void find_all(const node &n, typename std::list<node*>::iterator d_first) override
    {
//        for (auto it = __adjacency_list.begin(); it != __adjacency_list.end(); ++it)
//            if (*(it->first) == n)
//                *(d_first++) = it->first;
    }

    //calculates minimal distance between two given nodes using Dijkstra's algorithm
    //won't work if the graph contains edges with negative weight
    //the weight of the path is the return value of the method
    //the method can also write found path to either vector or list of pointers
    //d_first is the iterator to beginning of the sequence
    weight_t min_distance(node *from, node *to) override
    {
        return __count_min_distance(from, to);
    }

    weight_t min_distance(node *from, node *to, typename std::vector<node*>::iterator d_first) override
    {
        std::stack<node*> s_path;
        weight_t result = __count_min_distance(from, to, &s_path);
        __answer_from_stack(s_path, d_first);
        return result;
    }

    weight_t min_distance(node *from, node *to, typename std::list<node*>::iterator d_first) override
    {
        std::stack<node*> s_path;
        weight_t result = __count_min_distance(from, to, &s_path);
        __answer_from_stack(s_path, d_first);
        return result;
    }

    //calculates weight of a given path, which is given in either a list or vector of pointers to objects contained in graph
    //if it's unable to count the given path (in case graph contains not all the nodes) or the path doesn't exist returns -1
    weight_t path_weight(typename std::vector<node*>::iterator first, typename std::vector<node*>::iterator last) override
    {
        weight_t total = 0;
        for (auto it = first; it != last - 1; ++it)
        {
            auto f = __adjacency_list.find(*it);
            if (f == __adjacency_list.end())
                return -1;
            auto f_next = f->second.find(*(it + 1));
            if (f_next == f->second.end())
                return -1;
            total += f_next->second;
        }
        return total;
    }

    weight_t path_weight(typename std::list<node*>::iterator first, typename std::list<node*>::iterator last) override
    {
        weight_t total = 0;
        --last;
        for (auto it = first; it != last; ++it)
        {
            auto f = __adjacency_list.find(*it);
            if (f == __adjacency_list.end())
                return -1;
            auto f_next = f->second.find(*(++it));
            --it;
            if (f_next == f->second.end())
                return -1;
            total += f_next->second;
        }
        return total;
    }

    weight_t path_weight(node *first, node *last) override
    {
        weight_t total = 0;
        for (auto it = first; it != last - 1; ++it)
        {
            auto f = __adjacency_list.find(it);
            if (f == __adjacency_list.end())
                return -1;
            auto f_next = f->second.find(it + 1);
            if (f_next == f->second.end())
                return -1;
            total += f_next->second;
        }
        return total;
    }

    //check if the path between two nodes
    //exists without calculating the minimal path
    //in case of directed graph checks the path existence using bfs
    //in case of undirected graph uses DSU to speed up
    //the operation to be approximately time-constant
    bool path_exists(node *from, node *to) override
    {
        if (from == to)
            return true;
        std::unordered_set<node*> visited;
        std::queue<node*> q;
        q.push(from);
        visited.insert(from);
        while (!q.empty())
        {
            for (auto it = __adjacency_list[q.front()].begin(); it != __adjacency_list[q.front()].end(); ++it)
            {
                if (it->first == to)
                    return true;
                if (visited.find(it->first) == visited.end())
                {
                    visited.insert(it->first);
                    q.push(it->first);
                }
            }
            q.pop();
        }
        return false;
    }
};

#endif // ADJACENCY_LIST_GRAPH_H
