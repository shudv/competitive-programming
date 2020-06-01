#include "../common.h"

bool DP[10005][55];
int A[55];

int main()
{
    CASE
    {
        GET(N);

        int S = 0;
        REP(i, N)
        {
            scanf("%d", &A[i]);
            S += A[i];
        }

        int bS = (S+1)/2;
        REPI(s, 0, S)
        REP(i, N)
        {
            DP[s][i] = 
                (s == 0)
                || (i == 0 && s == A[i])
                || (i >= 1 && DP[s][i-1])
                || (s-A[i] >= 0 && i>=1 && DP[s-A[i]][i-1]);
            
            if (i == (N-1) && s >= bS && DP[s][i])
            {
                printf("%d\n", s - (S - s));
                s = S+1;
                break;
            }
        }
    }
    return 0;
}