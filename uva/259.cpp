#include "library/common.h"

typedef struct
{
    int from;
    int to;
    int capacity;
    int flow;
} edge;
vvi G(1000);
vector<edge> edges;
int application_count;
bool fin = false;

void add_edge(const edge &e)
{
    int edge_index = edges.size();
    edges.push_back(e);
    G[e.from].push_back(edge_index);
    G[e.to].push_back(edge_index);
}

char app_name(int index)
{
    return char(((index - 2) / 10) + 'A');
}

int app_index(char c, int count)
{
    return 2 + 10 * (c - 'A') + count;
}

int machine_index(char m)
{
    return 300 + (m - '0');
}

int compute_max_flow()
{
    int flow = 0, source = 0, target = 1;
    while (1)
    {
        qii q;
        mii edge_leading_to;
        si visited_vertices;
        q.push(PAIR(source, INF));
        int increase_in_flow = 0;

        while (!q.empty())
        {
            auto um = q.front();
            q.pop();
            int u = um.first;
            visited_vertices.insert(u);
            int minimum_flow = um.second;
            if (u == target)
            {
                // augment flow along the found path
                int current_vertex = u;
                while (current_vertex != source)
                {
                    auto e = &edges[edge_leading_to[current_vertex]];

                    // residual edge
                    if (e->from == current_vertex)
                    {
                        e->flow -= minimum_flow;
                        current_vertex = e->to;
                    }
                    else // real edge in graph
                    {
                        e->flow += minimum_flow;
                        current_vertex = e->from;
                    }
                }

                increase_in_flow = minimum_flow;
                break;
            }
            else
            {
                TR(edge_index, G[u])
                {
                    auto edge = edges[edge_index];

                    bool is_real_edge = edge.from == u;
                    int next_vertex = is_real_edge ? edge.to : edge.from;
                    int residual_capacity = is_real_edge ? (edge.capacity - edge.flow) : edge.flow;

                    if (residual_capacity > 0 && !HAS(visited_vertices, next_vertex))
                    {
                        q.push(PAIR(next_vertex, min(minimum_flow, residual_capacity)));
                        edge_leading_to[next_vertex] = edge_index;
                    }
                }
            }
        }

        flow += increase_in_flow;
        if (increase_in_flow == 0)
            break;
    }

    return flow;
}

void solve()
{
    // Add a common target vertex for all machines
    REPI(c, '0', '9')
        add_edge({machine_index(c), 1, 1, 0});

    int flow = compute_max_flow();
    if (flow == application_count)
    {
        REPI(machine, '0', '9')
        {
            int index = machine_index(machine);
            bool machine_used = false;
            TR(edge_index, G[index])
            {
                auto e = edges[edge_index];
                // Incoming edge with positive flow
                if (e.from != index && e.flow > 0)
                {
                    printf("%c", app_name(e.from));
                    machine_used = true;
                    break;
                }
            }

            if (!machine_used)
            {
                printf("_");
            }
        }
        printf(NL);
    }
    else
    {
        printf("!\n");
    }
}

int main()
{
    string line;
    while (getline(cin, line))
    {
        if (line == "")
        {
            solve();
            
            // re-init data structures for next case
            G.assign(1000, vi());
            edges.assign(0, {});
            application_count = 0;
        }
        else
        {
            char application = line[0];
            int count = line[1] - '0';
            string machines = line.substr(3);

            REP(i, 0, count)
            {
                application_count++;
                int app_vertex_index = app_index(application, i);
                add_edge({0, app_vertex_index, 1, 0});
                REP(j, 0, machines.size() - 1)
                {
                    add_edge({app_vertex_index, machine_index(machines[j]), 1, 0});
                }
            }
        }
    }
    solve();
    return 0;
}
