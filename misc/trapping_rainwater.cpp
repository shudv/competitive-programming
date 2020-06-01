#include "..\common.h"

int main()
{
    CASE
    {
        GET(N); vi A(N);
        REP(i, N) scanf("%d", &A[i]);

        int l = 0, r = N-1;
        int max_l = 0, max_r = 0;
        int water = 0;
        while (l <= r)
        {
            if (A[l] > A[r])
            {
                if (A[r] > max_r)
                    max_r = A[r];
                else
                    water += (max_r - A[r]);
                r--;
            }
            else
            {
                if (A[l] > max_l)
                    max_l = A[l];
                else
                    water += (max_l - A[l]);
                l++;
            }
        }
        printf("%d\n", water);
    }
    return 0;
}