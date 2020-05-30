#include "../common.h"

int max_rectangle_area(vi &H)
{
    int max_area = 0;
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
                int area = width * H[top];
                if (area > max_area)
                    max_area = area;
            }

            s.push(i);
        }
    }
    return max_area;
}

int main()
{
    CASE
    {
        GET(r, c);

        vvi A(r, vi(c, 0));
        REP(i, r)
        REP(j, c)
        {
            scanf("%d", &A[i][j]);
        }

        int max_area = 0;
        REP(i, r)
        {
            // Adjust row with numbers from previous row
            // to create a histogram
            if (i > 0)
                REP(j, c) if (A[i][j] == 1) A[i][j] += A[i-1][j];

            A[i].PUSH(0);
            int hist_area = max_rectangle_area(A[i]);
            if (hist_area > max_area) max_area = hist_area; 
        }

        printf("%d\n", max_area);
    }
    return 0;
}