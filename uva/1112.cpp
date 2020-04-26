#include "library/common.h"

class closer_vertex
{
    public:
    bool operator() (ii const& v1, ii const& v2) {
        return v1.first < v2.first;
    }
};

int main()
{
    int TEST; scanf("%d", &TEST);
    cin.ignore();
    cin.ignore();
    
    while(TEST--)
    {
        int N, E, T, M;
        cin>>N>>E>>T>>M;
        
        vvii G(N+1);

        while(M--)
        {
            int a,b,w;
            cin>>a>>b>>w;
            G[b].push_back(PAIR(a, w));
        }

        vi dist(N+1, INF); dist[E] = 0;
        // DEBUGC(dist, 10);
        priority_queue<ii, vii, closer_vertex> pq;
        pq.push(PAIR(dist[E], E));

        while(!pq.empty())
        {
            ii top = pq.top(); pq.pop();
            int d = top.first; int u = top.second;
            if (dist[u] == d)
            {
                TR(vw, G[u])
                {
                    int v = vw.first; int w = vw.second;
                    if (dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                        pq.push(PAIR(dist[v], v));
                    }
                }
            }
        }

        // DEBUGC(dist, 10);
        int count = 0;
        REPI(i, 1, N) if (dist[i] <= T) count++;
        printf("%d\n", count);
        if (TEST>0) printf("\n");
        cin.ignore();
    }
    return 0;
}