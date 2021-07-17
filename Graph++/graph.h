#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <set>
#include <stack>

//node is a class/structure that contains info about the node
//weight_type - any numeric type that can contain weight of an edge
template <class node, typename weight_type = double>
class graph
{
private:
    //first argument - node, second argument - nodes,
    //that are connected to the .first with weight
    std::map<node*, std::map<node*, weight_type>> nodes;
public:
    const weight_type default_edge_weight;

    //ctors
    graph(weight_type default_edge_weight = 1): default_edge_weight(default_edge_weight){}

    graph(const graph &g): default_edge_weight(g.default_edge_weight)
    {
        for (auto it = g.nodes.cbegin(); it != g.nodes.cend(); ++it)
        {
            std::map<node*, weight_type> connected;
            for (auto it_n = it->second.cbegin(); it_n != it->second.cend(); ++it_n)
                connected.emplace(new node *(it_n->first), it_n->second);
            this->nodes.emplace(new node *(it->first), std::move(connected));
        }
    }

    //methods to modify the graph

    void add_node(node *n)
    {
        nodes.emplace(n, std::map<node*, int>());
    }

    //connects nodes with an oriented edge
    bool connect(node *from, node *to)
    {
        auto f1 = nodes.find(from), f2 = nodes.find(to);
        if (f1 != nodes.end() && f2 != nodes.end())
        {
            f1->second[to]=  this->default_edge_weight;
            return true;
        }
        return false;
    }

    bool connect(node *from, node *to, weight_type weight)
    {
        auto f1 = nodes.find(from), f2 = nodes.find(to);
        if (f1 != nodes.end() && f2 != nodes.end())
        {
            f1->second[to] = weight;
            return true;
        }
        return false;
    }

    //connects nodes with a non-oriented edge
    bool connect_both(node *a, node *b)
    {
        auto f1 = nodes.find(a), f2 = nodes.find(b);
        if (f1 != nodes.end() && f2 != nodes.end())
        {
            f1->second[b] = default_edge_weight;
            f2->second[a] = default_edge_weight;
            return true;
        }
        return false;
    }

    bool connect_both(node *a, node *b, weight_type weight)
    {
        auto f1 = nodes.find(a), f2 = nodes.find(b);
        if (f1 != nodes.end() && f2 != nodes.end())
        {
            f1->second[b] = weight;
            f2->second[a] = weight;
            return true;
        }
        return false;
    }

    //disconnects two nodes
    bool disconnect(node *a, node *b)
    {
        auto f1 = nodes.find(a), f2 = nodes.find(b);
        if (f1 != nodes.end() && f2 != nodes.end())
        {
            f1->second.erase(b);
            f2->second.erase(a);
            return true;
        }
        return false;
    }

    //very slow function, need to think how to optimize node search
    template <class compare>
    node* find_if(compare comp)
    {
        for (auto it = nodes.cbegin(); it != nodes.cend(); ++it)
            if (comp(*(it->first)))
                return it->first;
        return nullptr;
    }

    //same here
    node* find(const node &n)
    {
        auto equals = [&n](const node &_n) {return !(_n < n) && !(n < _n);};
        for (auto it = nodes.cbegin(); it != nodes.cend(); ++it)
            if (equals(*(it->first)))
                return it->first;
        return nullptr;
    }

    weight_type min_distance(node *from, node *to)
    {
        if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end())
            return -1;
        std::map<node*, std::pair<weight_type, bool>> distances; //.first - total weight, .second - if the answer is found
        node *current = from;
        distances.emplace(from, std::make_pair(0, true));
        while (current != to)
        {
            auto f = nodes.find(current);
            auto f_d = distances.find(current);
            f_d->second.second = true;
            for (auto it = f->second.cbegin(); it != f->second.cend(); ++it)
            {
                auto f_it_first = distances.find(it->first);
                if (f_it_first == distances.end())
                    distances.emplace(it->first, std::make_pair(f_d->second.first + it->second, false));
                else if (f_it_first->second.first > f_d->second.first + it->second)
                    f_it_first->second.first = f_d->second.first + it->second;

            }
            weight_type min_w;
            node *min_n = nullptr;
            for (auto it = distances.begin(); it != distances.end(); ++it)
            {
                if (!it->second.second && (min_n == nullptr || it->second.first < min_w))
                {
                    min_n = it->first;
                    min_w = it->second.first;
                }
            }
            if (min_n == nullptr)
                return -1;
            current = min_n;
        }
        return distances[to].first;
    }

    template <class Iterator>
    void min_path(node *from, node *to, Iterator d_first)
    {
        if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end())
            return;
        std::map<node*, std::pair<weight_type, bool>> distances; //.first - total weight, .second - if the answer is found
        std::map<node*, node*> parents; //first - node; second - her parent
        node *current = from;
        distances.emplace(from, std::make_pair(0, true));
        while (current != to)
        {
            auto f = nodes.find(current);
            auto f_d = distances.find(current);
            f_d->second.second = true;
            for (auto it = f->second.cbegin(); it != f->second.cend(); ++it)
            {
                auto f_it_first = distances.find(it->first);
                if (f_it_first == distances.end())
                {
                    distances.emplace(it->first, std::make_pair(f_d->second.first + it->second, false));
                    parents[it->first] = current;
                }
                else if (f_it_first->second.first > f_d->second.first + it->second)
                {
                    f_it_first->second.first = f_d->second.first + it->second;
                    parents[it->first] = current;
                }
            }
            weight_type min_w;
            node *min_n = nullptr;
            for (auto it = distances.begin(); it != distances.end(); ++it)
            {
                if (!it->second.second && (min_n == nullptr || it->second.first < min_w))
                {
                    min_n = it->first;
                    min_w = it->second.first;
                }
            }
            if (min_n == nullptr)
                return;
            current = min_n;
        }
        std::stack<node*> s_path;
        s_path.push(to);
        while (s_path.top() != from)
            s_path.push(parents[s_path.top()]);
        Iterator it = d_first;
        while (!s_path.empty())
        {
            *it++ = s_path.top();
            s_path.pop();
        }
    }
};

#endif // GRAPH_H
