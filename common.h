#include<bits/stdc++.h>
using namespace std;

typedef long long            ll;
typedef unsigned long long   ull;
typedef vector<int>          vi;
typedef queue<int>           qi;
typedef priority_queue<int>  pqi;
typedef vector<vi>           vvi;
typedef set<int>             si;
typedef map<int,int>         mii;
typedef map<string,int>      msi;
typedef pair<int,int>        ii;
typedef vector<ii>           vii;
typedef queue<ii>            qii;
typedef vector<vii>          vvii;

#define NL                   "\n"
#define INF                  2000000000

#define PAIR                 make_pair
#define REP(i,a,b)           for(int i=int(a); i<int(b); i++)
#define REPI(i, a, b)        for (int i = int(a); i <= int(b); i++)
#define TR(it, c)            for (auto &it : c)
#define ALL(c)               c.begin(), c.end()
#define TESTS                int tests; scanf("%d", &tests); REPI(test_index, 1, tests)
#define FIELD(w)             setfill(' ') << setw(w)
#define HAS(c, it)           ((c).find(it) != (c).end())
#define IN(x)                int x; scanf("%d", &x)