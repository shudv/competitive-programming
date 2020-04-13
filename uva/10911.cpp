#include<bits/stdc++.h>
using namespace std;

typedef long long           ll;
typedef unsigned long long  ull;
typedef vector<int>         vi;
typedef queue<int>          qi;
typedef priority_queue<int> pqi;
typedef vector<vi>          vvi;
typedef pair<int,int>       ii;
typedef set<int>            si;
typedef map<string,int>     msi;

#define IN(n) int (n); scanf("%d",&(n))
#define REP(i,a,b) for(int i=int(a); i<int(b); i++)
#define TR(c,it) for (typeof((c).begin()) it=(c).begin(); it!=(c).end(); it++)
#define ALL(c) c.begin(), c.end()
#define TESTS get(tests); while (tests--)

#define NL "\n"

#define MAXN 16
int N;
double dist[MAXN][MAXN], dp[1<<16];

double solve(int mask)
{
    if (dp[mask] > -0.5) {
        return dp[mask];
    }

    if (mask == ((1<<(2*N)) - 1)) {
        return dp[mask] = 0;
    }

    double matching_value = 32767.0 * 32767.0;
    REP(i, 0, 2*N)
    {
        if((mask & (1<<i)) == 0)
        {
            REP(j, i+1, 2*N)
            {
                if ((mask & (1<<j)) == 0)
                {
                    matching_value = min(matching_value, dist[i][j] + solve(mask | 1<<i | 1<<j));
                }
            }
        }
    }

    return dp[mask] = matching_value;
}

int main()
{
    int caseNo = 1;
    do
    {
        scanf("%d", &N);
        if(N==0) break;

        vi x(MAXN), y(MAXN);
        REP(i, 0, 2*N)
        {
            char name[100];
            scanf("%s", name);
            IN(X); IN(Y);
            x[i] = X;
            y[i] = Y;
        }

        REP(i, 0, 2*N)
        REP(j, 0, 2*N)
        {
            dist[i][j] = sqrt(((x[i]-x[j])*(x[i]-x[j])) + ((y[i]-y[j])*(y[i]-y[j])));
        }

        for (int i=0;i<(1<<(2*N));i++) {
            dp[i] = -1.0;
        }

        printf("Case %d: %.2lf\n", caseNo++, solve(0));
    }
    while(true);
    return 0;
}