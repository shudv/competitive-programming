#include "common.h"

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
        
        if (increase_in_flow == 0) break;
        flow += increase_in_flow;
    }
    return flow;
}
