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
typedef set<int>            si;
typedef map<string,int>     msi;

#define MP           make_pair
#define NL           "\n"
#define REP(i,a,b)   for(int i=int(a); i<int(b); i++)
#define REPI(i,a,b)  for(int i=int(a); i<=int(b); i++)
#define TR(it,c)     for (auto const & it: c)
#define ALL(c)       c.begin(), c.end()
#define TESTS        int tests; scanf("%d", &tests); REPI(test_index, 1, tests)

#define DEBUGC(c,w)       cout<<"[ "; TR(it, c) { cout<<setfill(' ')<<setw(w)<<it<<" "; } cout<<"]"<<NL; }
#define DEBUGA(a,n,w)     cout<<"[ "; REP(debug_x, 0, n) { cout<<setfill(' ')<<setw(w)<<a[debug_x]<<" "; } cout<<"]"<<NL;
#define DEBUG2A(a,m,n,w)  REP(debug_y, 0, m) { DEBUGA(a[debug_y], n, w); }


#define MAXN 2005
int dist[MAXN][MAXN];
vii neighbours = { MP(0, -1), MP(-1, 0), MP(+1, 0), MP(0, +1)};

int bfs(vii& mall)
{
    qii Q;
    TR(it, mall)
    {
        Q.push(it);
    }
    do
    {
        ii next = Q.front();
        Q.pop();

        int distance = dist[next.first][next.second];
        int neighbour_least_distance = distance+1;
        TR(neighbour, neighbours)
        {
            int neighbour_x = next.first + neighbour.first;
            int neighbour_y = next.second + neighbour.second;

            if (neighbour_x >=0 && neighbour_x < MAXN && neighbour_y >=0 && neighbour_y < MAXN)
            {
                int neighbour_distance = dist[neighbour_x][neighbour_y];
            
                // If other mall is found return distance
                if (neighbour_distance == -1) return neighbour_least_distance;

                // Else update distance if it is smaller
                if (neighbour_least_distance < neighbour_distance)
                {
                    dist[neighbour_x][neighbour_y] = neighbour_least_distance;
                    Q.push(MP(neighbour_x, neighbour_y));
                    //cout<<"push "<<neighbour_x<<","<<neighbour_y<<":"<<neighbour_least_distance<<NL;
                    //print();
                }
            }
        }
    }
    while(!Q.empty());
    return -1;
}

int main()
{
    do
    {
        REP(i, 0, MAXN) REP(j, 0, MAXN) dist[i][j] = 9999;

        //print();
        // source mall
        vii source_mall;
        int n; cin >> n;
        if (n == 0) return 0;

        while (n--)
        {
            int x, y;
            cin >> x >> y;
            source_mall.push_back(MP(x, y));
            // Mall's vertices are at 0 distance from itself
            dist[x][y] = 0;
        }

        // target mall
        cin>>n;
        while(n--)
        {
            int x,y;
            cin>>x>>y;
            // mark target veriices distinctly
            dist[x][y] = -1;
        }

        // DEBUG2A(dist, 5, 5, 5);
        printf("%d\n", bfs(source_mall));
        //print();
    }
    while (true);
    return 0;
}