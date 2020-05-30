#include "../common.h"

ll max_rectangle_area(vector<ll> &H)
{
    ll max_area = 0;
    sti s;
    REP(i, H.size())
    {
        if (s.empty() || H[i] > H[s.top()])
            s.push(i);
        else
        {
            while (!s.empty() && H[s.top()] >= H[i])
            {
                int top = TOP(s);
                int width = s.empty() ? i : (i - (s.top() + 1));
                ll area = width * H[top];
                if (area > max_area)
                    max_area = area;
            }

            s.push(i);
        }
    }
}

int main()
{
    CASE
    {
        GET(N);
        vector<ll> H(N);
        REP(i, N) scanf("%lld", &H[i]);
        H.PUSH(0);
        printf("%lld\n", max_rectangle_area(H));
    }
    return 0;
}