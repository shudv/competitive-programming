#include "../common.h"

int main()
{
    int t=0;
    LOOP
    {
        GET(C, S, Q);
        if (C == 0) break;

        if (t > 0) printf("\n");
        vvi W(C+1, vi(C+1, INF));

        REP(S)
        {
            GET(c1, c2, d);
            W[c1][c2] = d;
            W[c2][c1] = d;
            W[c1][c1] = 0;
            W[c2][c2] = 0; 
        }

        REPI(k, C)
        REPI(u, C)
        REPI(v, C)
        {
            W[u][v] = MIN(W[u][v], MAX(W[u][k], W[k][v]));
        }
        
        printf("Case #%d\n", ++t);
        REP(Q)
        {
            GET(c1, c2);
            if (W[c1][c2] == INF) printf ("no path\n");
            else printf("%d\n", W[c1][c2]); 
        }
    }
    return 0;
}