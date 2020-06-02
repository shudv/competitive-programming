#include<bits/stdc++.h>
using namespace std;

#pragma region types_and_macros

// Types
typedef long long               ll;
typedef unsigned long long      ull;
typedef vector<int>             vi;
typedef queue<int>              qi;
typedef stack<int>              sti;
typedef priority_queue<int>     pqi;
typedef vector<vi>              vvi;
typedef set<int>                si;
typedef map<int,int>            mii;
typedef map<string,int>         msi;
typedef pair<int,int>           ii;
typedef vector<ii>              vii;
typedef queue<ii>               qii;
typedef vector<vii>             vvii;

// Constants
#define NL                      "\n"
#define INF                     2000000000
#define NONE                    -1
#define TRUE                    1
#define FALSE                   0

// Macros for defining and reading one or more integers
#define GET(...)                OVERLOAD(GET, __VA_ARGS__)
#define GET1(a)                 int a; scanf("%d", &a)
#define GET2(a, b)              GET1(a); GET1(b)
#define GET3(a, b, c)           GET2(a, b); GET1(c)
#define GET4(a, b, c, d)        GET3(a, b, c); GET1(d)

// Macros for defining and reading one or more float values
#define GETf(...)               OVERLOAD(GETf, __VA_ARGS__)
#define GETf1(a)                float a; scanf("%f", &a)
#define GETf2(a, b)             GETf1(a); GETf1(b)

// Macros for defining and reading one or more float values
#define GETf(...)               OVERLOAD(GETf, __VA_ARGS__)
#define GETf1(a)                float a; scanf("%f", &a)
#define GETf2(a, b)             GETf1(a); GETf1(b)

// Iteration macros
#define REP(...)                OVERLOAD(REP, __VA_ARGS__)
#define REP1(a)                 REP2(i, a)
#define REP2(i, a)              REP3(i, 0, a)
#define REP3(i, a, b)           for(int i=int(a); i<int(b); i++)
#define REPI(...)               OVERLOAD(REPI, __VA_ARGS__)
#define REPI2(i, a)             REPI3(i, 1, a)
#define REPI3(i, a, b)          REP3(i, a, b+1)
#define LOOP                    while (true)

// STL macros
#define PAIR                    make_pair
#define PUSH                    push_back
#define TOP(q)                  q.top(); q.pop();
#define FRONT(q)                q.front(); q.pop();
#define TR(it, c)               for (auto &it : c)
#define ALL(c)                  c.begin(), c.end()
#define HAS(c, it)              ((c).find(it) != (c).end())
#define PQC(t, c)               class c { public: bool operator()(const t &i1, const t &i2)
#define PQ(t, c)                priority_queue<t, vector<t>, c>
#define RES(...)                OVERLOAD(RES, __VA_ARGS__)
#define RES1(v)                 RES2(v, 0)
#define RES2(v, n)              v.clear(); v.resize(n)
#define RES3(v, n, c)           v.assign(n, c)

// Max, Min
#define MAX(...)                OVERLOAD(MAX, __VA_ARGS__)
#define MAX2(a, b)              max(a, b)
#define MAX3(a, b, c)           MAX2(MAX2(a, b), c)
#define MAX4(a, b, c, d)        MAX2(MAX3(a, b, c), d)
#define MIN(...)                OVERLOAD(MIN, __VA_ARGS__)
#define MIN2(a, b)              min(a, b)
#define MIN3(a, b, c)           MIN2(MIN2(a, b), c)
#define MIN4(a, b, c, d)        MIN2(MIN3(a, b, c), d)

// Graph specific
#define OTHER(e, u)             (e.first == u ? e.second : e.first)

// Miscellaneous
#define CASE                    GET(_cases); REPI(case_number, 1, _cases)
#define FIELD(w)                setfill(' ') << setw(w)

// Following macros enable overloading of macro names for variable number of arguments 
#define GET_COUNT( _1, _2, _3, _4, COUNT, ... ) COUNT
#define VA_SIZE(...)            GET_COUNT( __VA_ARGS__, 4, 3, 2, 1 )
#define OVERLOAD(m, ...)        CAT(m, VA_SIZE(__VA_ARGS__))(__VA_ARGS__)
#define CAT(m, n)               CAT_(m, n)
#define CAT_(a, b)              a ## b

#pragma endregion
