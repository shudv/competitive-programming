#include "../common.h"

typedef struct
{
    int parent;
    int depth;
    int diameter;
} vertex_info;

int get_farthest_vertex(const vvi &G, int u)
{
    int farthest_vertex;
    qi q;
    vi visited(G.size(), FALSE);

    q.push(u);
    while (!q.empty())
    {
        int u = FRONT(q);

        // The last vertext discovered by BFS is the farthest vertex
        farthest_vertex = u;

        visited[u] = TRUE;
        TR(v, G[u])
        {
            if (visited[v] == FALSE)
            {
                q.push(v);
            }
        }
    }

    return farthest_vertex;
}

void calculate_vertex_info(const vvi &G, int root, vector<vertex_info> &vertex_info)
{
    REP(i, G.size()) vertex_info[i].parent = NONE;

    sti s;
    s.push(root);

    while (!s.empty())
    {
        int u = s.top();
        bool children_processing_pending = false;

        TR(v, G[u])
        {
            if (vertex_info[v].parent == NONE)
            {
                vertex_info[v].parent = u;
                s.push(v);
                children_processing_pending = true;
                break;
            }
        }

        if (!children_processing_pending)
        {
            int deepest_child_depth = -1;
            int second_deepest_child_depth = -1;
            int largest_child_diameter = -1;

            TR(v, G[u])
            {
                if (v != vertex_info[u].parent)
                {
                    int d = vertex_info[v].depth;
                    if (d > deepest_child_depth)
                    {
                        second_deepest_child_depth = deepest_child_depth;
                        deepest_child_depth = d;
                    }
                    else if (d > second_deepest_child_depth && d <= deepest_child_depth)
                    {
                        second_deepest_child_depth = d;
                    }

                    if (vertex_info[v].diameter > largest_child_diameter)
                        largest_child_diameter = vertex_info[v].diameter;
                }

                vertex_info[u].depth = deepest_child_depth + 1;

                int diameter_length_via_u = deepest_child_depth + second_deepest_child_depth + 2;
                int diameter_length_with_u_as_endpoint = deepest_child_depth + 1;
                vertex_info[u].diameter = MAX(largest_child_diameter, diameter_length_with_u_as_endpoint, diameter_length_via_u);
            }

            s.pop();
        }
    }
}

// Find midpoint of subtree rooted at root
int find_mid_point(const vvi &G, int root, int root_parent)
{
    // We want to traverse only the subtree at root
    vi visited(G.size(), FALSE);
    visited[root_parent] = TRUE;

    // Find one end of the diameter
    int diameter_start;
    qi q;
    q.push(root);
    while (!q.empty())
    {
        int u = FRONT(q);
        visited[u] = TRUE;
        diameter_start = u;
        TR(v, G[u])
        {
            if (visited[v] == FALSE)
                q.push(v);
        }
    }

    // Find the other end of the diameter while keeping track of parents
    int diameter_end;
    vi parent(G.size(), NONE);

    fill(ALL(visited), FALSE);
    visited[root_parent] = TRUE;

    q.push(diameter_start);
    while (!q.empty())
    {
        int u = FRONT(q);

        diameter_end = u;
        visited[u] = TRUE;

        TR(v, G[u])
        {
            if (visited[v] == FALSE)
            {
                parent[v] = u;
                q.push(v);
            }
        }
    }

    // Find diameter edge length
    int diameter_edge_length = 0;
    int u = diameter_end;
    while (u != diameter_start)
    {
        diameter_edge_length++;
        u = parent[u];
    }

    // Find half length of the diameter and move along from one end to the middle
    int half_length = diameter_edge_length / 2;
    int mid_point = diameter_end;
    REP(i, half_length)
    mid_point = parent[mid_point];

    return mid_point;
}

int main()
{
    CASE
    {
        GET(n);
        vvi G(n + 1);
        REP(i, n - 1)
        {
            GET(a, b);
            G[a].PUSH(b);
            G[b].PUSH(a);
        }

        // Calculate diametrically opposite endpoints
        int diameter_start = get_farthest_vertex(G, 1);
        int diameter_end = get_farthest_vertex(G, diameter_start);

        // Calculate depth and diameter information with both endpoints
        vector<vertex_info> vertex_info_1(G.size());
        calculate_vertex_info(G, diameter_start, vertex_info_1);

        vector<vertex_info> vertex_info_2(G.size());
        calculate_vertex_info(G, diameter_end, vertex_info_2);

        // Find the edge along the diameter splitting which can yield the least possible diameter
        int least_possible_diameter = INF;
        ii split;
        int v = diameter_end;
        while (v != diameter_start)
        {
            // diameter of subtree rooted at v if v --> parent[v] edge is split
            int d1 = vertex_info_1[v].diameter;

            // diameter of subtree rooted at parent[v] if v --> parent[v] edge is split
            int d2 = vertex_info_2[vertex_info_1[v].parent].diameter;

            // calculate the minmum possible diameter of the tree created by joining the two subtrees
            int possible_diameter = MAX(((d1 + 1) / 2) + ((d2 + 1) / 2) + 1, d1, d2);

            if (possible_diameter < least_possible_diameter)
            {
                least_possible_diameter = possible_diameter;
                split = PAIR(v, vertex_info_1[v].parent);
            }

            v = vertex_info_1[v].parent;
        }

        // Find the midpoints of diameters in two subtrees
        int mid_point_1 = find_mid_point(G, split.second, split.first);
        int mid_point_2 = find_mid_point(G, split.first, split.second);
        printf("%d\n", least_possible_diameter);
        printf("%d %d\n", split.second, split.first);
        printf("%d %d\n", mid_point_1, mid_point_2);
    }
    return 0;
}