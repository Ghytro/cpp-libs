#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include <vector>

class Vertex
{
    friend class Graph;
private:
    size_t id;
    std::vector<std::pair<Vertex*, size_t>> adjacent;
public:
    Vertex(size_t _id);
    void connect(Vertex *v, size_t distance);
};

Vertex::Vertex(size_t _id)
{
    id = _id;
}

void Vertex::connect(Vertex *v, size_t distance)
{
    if (adjacent.size() == 0)
    {
        adjacent.push_back({v, distance});
        return;
    }
    size_t l = 0, r = adjacent.size();
    while (l != r)
    {
        size_t now = (l + r) / 2;
        if (adjacent[now].second >= distance)
            r = now;
        else
            l = now + 1;
    }
    adjacent.insert(adjacent.begin() + l, {v, distance});
}

#endif // VERTEX_H_INCLUDED
