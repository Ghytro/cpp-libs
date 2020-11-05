#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "vertex.h"

const size_t no_path = 4294967295;

class Graph
{
private:
    std::vector<Vertex> vertexes;
    std::vector<size_t> rast;
    std::vector<bool> label;
    bool dijkstra_counting = false;
    void dijkstra(size_t v, size_t &vf);
    bool is_oriented;
public:
    Graph::Graph(bool _is_oriented)
    void add_vertex();
    Vertex get_vertex_by_id(size_t _id);
    void connect(size_t v1, size_t v2, size_t distance);
    size_t distance(size_t v1, size_t v2);
};

Graph::Graph(bool _is_oriented)
{
    is_oriented = _is_oriented;
}

void Graph::add_vertex()
{
    Vertex v = Vertex(vertexes.size());
    vertexes.push_back(v);
}

Vertex Graph::get_vertex_by_id(size_t _id)
{
    return vertexes[_id];
}

void Graph::connect(size_t v1, size_t v2, size_t distance)
{
    vertexes[v1].connect(&vertexes[v2], distance);
    if (!is_oriented)
        vertexes[v2].connect(&vertexes[v1], distance);
}

void Graph::dijkstra(size_t v, size_t &vf)
{
    if (!dijkstra_counting)
    {
        rast = std::vector<size_t> (vertexes.size(), UINT_MAX);
        label = std::vector<bool> (vertexes.size(), false);
        rast[v] = 0;
        dijkstra_counting = true;
    }

    label[v] = true;

    for (auto i: vertexes[v].adjacent)
    {

        if (!label[i.first->id] && rast[v] + i.second < rast[i.first->id])
            rast[i.first->id] = rast[v] + i.second;
    }

    size_t _min = UINT_MAX; long long ind = -1;
    for (size_t i = 0; i < rast.size(); ++i)
        if (rast[i] < _min && !label[i])
        {
            _min = rast[i];
            ind = i;
        }

    if (ind != -1 && ind != vf)
        Graph::dijkstra(ind, vf);
    else
        dijkstra_counting = false;
}

size_t Graph::distance(size_t v1, size_t v2)
{
    dijkstra(v1, v2);
    return ((rast[v2] == UINT_MAX) ? (no_path) : rast[v2]);
}

#endif // GRAPH_H_INCLUDED
