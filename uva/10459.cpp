#include "..\common.h"

#define UNKNOWN -1

void calculate_depth(vvi &G, int u, int parent, vi &depth)
{
    int max_depth = -1;
    TR(v, G[u])
    {
        if (v != parent)
        {
            calculate_depth(G, v, u, depth);
            if (depth[v] > max_depth)
            {
                max_depth = depth[v];
            }
        }
    }
    depth[u] = max_depth + 1;
}

void calculate_depth_as_root(
    vvi &G,
    int u,
    int parent,
    int largest_path_to_parent,
    vi &depth,
    vi &depth_as_root)
{
    if (largest_path_to_parent + 1 > depth[u])
    {
        depth_as_root[u] = largest_path_to_parent + 1;
        TR(v, G[u])
        {
            if (v != parent)
                calculate_depth_as_root(G, v, u, depth_as_root[u], depth, depth_as_root);
        }
    }
    else
    {
        depth_as_root[u] = depth[u];

        int deepest_child_depth = -1;
        int second_deepest_child_depth = -1;

        TR(v, G[u])
        {
            if (v != parent)
            {
                if (depth[v] > deepest_child_depth)
                {
                    second_deepest_child_depth = deepest_child_depth;
                    deepest_child_depth = depth[v];
                }
                else if (depth[v] <= deepest_child_depth && depth[v] > second_deepest_child_depth)
                {
                    second_deepest_child_depth = depth[v];
                }
            }
        }

        TR(v, G[u])
        {
            if (v != parent)
            {
                if (depth[v] == deepest_child_depth)
                    calculate_depth_as_root(G, v, u, max(second_deepest_child_depth, largest_path_to_parent) + 1, depth, depth_as_root);
                else
                    calculate_depth_as_root(G, v, u, deepest_child_depth + 1, depth, depth_as_root);
            }
        }
    }
}

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        vvi G(n + 1);
        REPI(u, n)
        {
            GET(m);
            REP(j, m)
            {
                GET(v);
                G[u].PUSH(v);
            }
        }

        int initial_root = 2;
        vi depth(n + 1, 0);
        calculate_depth(G, initial_root, -1, depth);

        vi depth_as_root(n + 1, 0);
        depth_as_root[initial_root] = depth[initial_root];
        calculate_depth_as_root(G, initial_root, -1, -1, depth, depth_as_root);

        vi best_roots;
        int min_depth = INF;
        vi worst_roots;
        int max_depth = 0;

        REPI(i, n)
        {
            int h = depth_as_root[i];

            if (h > max_depth)
            {
                max_depth = h;
                worst_roots.clear();
                worst_roots.PUSH(i);
            }
            else if (h == max_depth)
            {
                worst_roots.PUSH(i);
            }

            if (h < min_depth)
            {
                min_depth = h;
                best_roots.clear();
                best_roots.PUSH(i);
            }
            else if (h == min_depth)
            {
                best_roots.PUSH(i);
            }
        }

        printf("Best Roots  :");
        TR(r, best_roots)
        printf(" %d", r);
        printf("\n");

        printf("Worst Roots :");
        TR(r, worst_roots)
        printf(" %d", r);
        printf("\n");
    }
    return 0;
}