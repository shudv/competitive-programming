#include "..\common.h"

#define MAXD 1005

int main()
{
    CASE
    {
        GET(n, r);
        vvi W(n, vi(n, MAXD));

        REP(r)
        {
            GET(a, b);
            W[a][b] = W[b][a] = 1;
        }

        GET(source, destination);
        REP(n) W[i][i] = 0;

        REP(k, n)
        REP(u, n)
        REP(v, n)
            W[u][v] = MIN(W[u][v], W[u][k] + W[k][v]);

        int largest_distance = 0;
        REP(n)
        {
            int distance = W[source][i] + W[i][destination];
            if (distance > largest_distance)
                largest_distance = distance;
        }

        printf("Case %d: %d\n", case_number, largest_distance);
    }
    return 0;
}