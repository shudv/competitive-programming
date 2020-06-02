#include "../common.h"

typedef pair<double, int> vertex;
PQC(vertex, vc)
{
    return i1.first > i2.first;
}};

int main()
{
    CASE
    {
        GET(N, R);
        vii V(N);
        REP(i, N)
        {
            GET(x, y);
            V[i] = PAIR(x, y);
        }

        vi visited(N, FALSE);
        
        PQ(vertex, vc) pq;
        pq.push(PAIR(0, 0));

        double rail = 0;
        double road = 0;
        int states = 1;
        int visit_count = 0;

        while(!pq.empty() && visit_count < N)
        {
            auto du = TOP(pq);
            int u = du.second;
            double d = du.first;

            if (visited[u] == FALSE)
            {
                visited[u] = TRUE;
                visit_count++;

                if (d >= R && d > 0)
                {
                    states++;
                    rail += d;
                }
                else
                {
                    road += d;
                }

                REP(v, 0, N)
                if (visited[v] == FALSE)
                {
                    double distance = hypot(V[v].first - V[u].first, V[v].second - V[u].second); 
                    pq.push(PAIR(distance, v));
                }
            }
        }

        printf("Case #%d: %d %d %d\n", case_number, states, int(round(road)), int(round(rail)));
    }
    return 0;
}