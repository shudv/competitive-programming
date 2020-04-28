#include "..\common.h"

typedef struct
{
    int x;
    int y;
    int penguins;
    int strength;
} floe;

typedef struct
{
    int from;
    int to;
    int capacity;
    int flow;
} edge;

int compute_max_flow(
    const vvi &G,
    vector<edge> &edges,
    const int source,
    const int target)
{
    int flow = 0;
    while (true)
    {
        // queue containing vertices along with the maximum
        // permissible flow on the path source ----> vertex
        qii bfs_queue;
        bfs_queue.push(PAIR(source, INF));

        // edge leading to a particular vertex on the
        // shorted path from source
        mii edge_leading_to;

        int increase_in_flow = 0;
        while (!bfs_queue.empty())
        {
            auto um = bfs_queue.front();
            bfs_queue.pop();
            int found_vertex = um.first;
            int maximum_flow = um.second;

            if (found_vertex != target)
            {
                TR(edge_index, G[found_vertex])
                {
                    auto edge = edges[edge_index];

                    // Choose next vertex and calculate residual capacity
                    // based on whether it's a residual edge or a real edge
                    bool is_real_edge = (edge.from == found_vertex);
                    int next_vertex = is_real_edge ? edge.to : edge.from;
                    int residual_capacity = is_real_edge ? (edge.capacity - edge.flow) : edge.flow;

                    int residual_flow = min(maximum_flow, residual_capacity);
                    if (residual_flow > 0 && !HAS(edge_leading_to, next_vertex))
                    {
                        bfs_queue.push(PAIR(next_vertex, residual_flow));
                        edge_leading_to[next_vertex] = edge_index;
                    }
                }
            }
            else if (found_vertex == target)
            {
                // augment flow along the path source ----> target
                increase_in_flow = maximum_flow;
                int current_vertex = target;
                while (current_vertex != source)
                {
                    auto e = &edges[edge_leading_to[current_vertex]];
                    if (e->from == current_vertex)
                    {
                        // Revert flow along the residual edge
                        e->flow -= increase_in_flow;
                        current_vertex = e->to;
                    }
                    else
                    {
                        // Increment flow along the real edge
                        e->flow += increase_in_flow;
                        current_vertex = e->from;
                    }
                }
                break;
            }
        }

        if (increase_in_flow == 0)
            break;
        flow += increase_in_flow;
    }
    return flow;
}

inline void add_edge(vvi &G, vector<edge> &edges, const edge &e)
{
    int edge_index = edges.size();
    edges.PUSH(e);
    G[e.from].PUSH(edge_index);
    G[e.to].PUSH(edge_index);
}

inline int floe_out_index(int floe, int n) { return 2 + n + floe; }
inline int floe_in_index(int floe, int n) { return 2 + floe; }

int main()
{
    CASE
    {
        GET(n);
        GETf(d);

        vector<floe> floes;
        int total_penguins = 0;
        REP(i, n)
        {
            GET(x, y, penguins, strength);
            floes.PUSH({x, y, penguins, strength});
            total_penguins += penguins;
        }

        vvi G((2*n) + 2);
        vector<edge> edges;
        int source = 0, target = 1;
        
        REP(i, n)
        {
            auto f = floes[i];

            // Bound the number of penguins that can jump off of a floe
            add_edge(G, edges, {floe_in_index(i, n), floe_out_index(i, n), f.strength, 0});

            if (floes[i].penguins > 0)
            {
                // Place penguins on floes according to given initial conditions
                add_edge(G, edges, {source, floe_in_index(i, n), f.penguins, 0});
            }
        }

        REP(i, n)
        REP(j, i+1, n)
        {
            auto f1 = floes[i];
            auto f2 = floes[j];
            auto dx = f1.x - f2.x;
            auto dy = f1.y - f2.y;
            // If the floes are nearby, any number of penguins can jump onto them from each other
            if (sqrt((dx*dx) + (dy*dy)) < d)
            {
                add_edge(G, edges, { floe_out_index(i, n), floe_in_index(j, n), INF, 0 });
                add_edge(G, edges, { floe_out_index(j, n), floe_in_index(i, n), INF, 0 });
            }
        }

        // Test if all penguins can collect on a particular floe
        vi accessible_floes;
        REP(i, n)
        {
            // Add a target edge from floe i to collect all penguins
            add_edge(G, edges, { floe_in_index(i, n), target, total_penguins, 0 });

            if (compute_max_flow(G, edges, source, target) == total_penguins)
            {
                accessible_floes.PUSH(i);
            }

            // Remove the edge from the target
            edges.pop_back();
            G[target].pop_back();
            G[floe_in_index(i, n)].pop_back();

            // Reset all flows
            TR(e, edges) e.flow = 0;
        }

        if (accessible_floes.size() > 0)
        {
            printf("%d", accessible_floes[0]);
            REP(i, 1, accessible_floes.size())
                printf(" %d", accessible_floes[i]);
        }
        else
        {
            printf("-1");
        }
        printf("\n");
    }
    return 0;
}