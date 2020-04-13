#pragma region header
#include<bits/stdc++.h>
using namespace std;

typedef long long           ll;
typedef unsigned long long  ull;
typedef pair<int,int>       ii;
typedef vector<int>         vi;
typedef vector<ii>          vii;
typedef queue<int>          qi;
typedef queue<ii>           qii;
typedef priority_queue<int> pqi;
typedef vector<vi>          vvi;
typedef vector<vii>         vvii;
typedef set<int>            si;
typedef map<string,int>     msi;

#define NL    "\n"
#define PAIR  make_pair
#define INF   2000000000

#define REP(i,a,b)  for(int i=int(a); i<int(b); i++)
#define REPI(i,a,b) for(int i=int(a); i<=int(b); i++)
#define TR(it,c)    for (auto const & it: c)
#define ALL(c)      c.begin(), c.end()
#define TESTS       int tests; scanf("%d", &tests); REPI(test_index, 1, tests)

#define DEBUGC(c,w)       { cout<<"[ "; TR(debug_it,c) { cout<<setfill(' ')<<setw(w)<<debug_it<<" "; } cout<<"]"<<NL; }
#define DEBUGA(a,n,w)     { cout<<"[ "; REP(debug_x, 0, n) { cout<<setfill(' ')<<setw(w)<<a[debug_x]<<" "; } cout<<"]"<<NL; }
#define DEBUG2A(a,m,n,w)  { REP(debug_y, 0, m) { DEBUGA(a[debug_y], n, w); } }
#pragma endregion

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