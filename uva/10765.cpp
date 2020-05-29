#include "..\common.h"

vvi G;

bool compare(ii t1, ii t2) 
{
    return t1.second != t2.second ? t1.second > t2.second : t1.first < t2.first;
} 

vii solve()
{
    int t = 0;
    vi time(G.size(), NONE);
    vi back(G.size(), NONE);
    vi children(G.size(), 0);
    vi parent(G.size(), NONE);

    sti s;
    int root = 0;
    time[root] = t++;
    back[root] = time[root];
    s.push(root);

    while (!s.empty())
    {
        int u = s.top();

        children[u] = 0;
        bool subtree_processed = true;
        TR (v, G[u])
        {
            if (v != parent[u])
            {
                if (time[v] == NONE)
                {
                    time[v] = t++;
                    back[v] = time[v];
                    parent[v] = u;
                    subtree_processed = false;
                    s.push(v);
                    break;
                }
                else
                {
                    back[u] = MIN(back[u], back[v]);
                    if (back[v] >= time[u] && parent[v] == u)
                        children[u]++;
                }
            }
        }

        if (subtree_processed) s.pop();
    }

    vii targets;
    REP(u, G.size())
        targets.PUSH(PAIR(u, children[u] + (u == root ? 0 : 1)));

    sort(ALL(targets), compare);
    return targets;
}

int main()
{
    LOOP
    {
        GET(n, m);
        if (n == 0) break;

        RES(G, n);
        LOOP
        {
            GET(x, y);
            if (x == -1) break;

            G[x].PUSH(y); 
            G[y].PUSH(x);
        }

        auto targets = solve();
        REP(m) printf("%d %d\n", targets[i].first, targets[i].second);
        printf(NL);
    }
    return 0;
}