#include "..\common.h"

struct edge { int u; int v; int l; };
PQC(edge, ec)
{
    return i1.l > i2.l;
}};

vi P, W;

int find(int u)
{
    if (P[u] == NONE)
        return u;
    else
    {
        int p = find(P[u]);
        P[u] = p;
        return p;
    }
}

void connect(int u, int v)
{
    int pu = find(u);
    int pv = find(v);

    if (W[pu] > W[pv])
    {
        P[pv] = pu;
        W[pu] += W[pv];
    }
    else
    {
        P[pu] = pv;
        W[pv] += W[pu];
    }
}

bool connected(int u, int v)
{
    return find(u) == find(v);
}

int main()
{
    LOOP
    {
        GET(m, n);
        if (m==0) break;
        RES(P, m, NONE);
        RES(W, m, 1);

        int cost = 0;
        PQ(edge, ec) pq;
        REP(n)
        {
            GET(u, v, l);
            pq.push({u, v, l});
            cost += l;
        }

        int min_cost = 0;
        while (!pq.empty())
        {
            auto e = TOP(pq);

            if (!connected(e.u, e.v))
            {
                connect(e.u, e.v);
                min_cost += e.l;
            }
        }

        printf("%d\n", cost - min_cost);
    }
    return 0;
}