#pragma region header
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef queue<int> qi;
typedef queue<ii> qii;
typedef priority_queue<int> pqi;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef set<int> si;
typedef map<string, int> msi;

#define NL "\n"
#define PAIR make_pair
#define INF 2000000000

#define REP(i, a, b) for (int i = int(a); i < int(b); i++)
#define REPI(i, a, b) for (int i = int(a); i <= int(b); i++)
#define TR(c, it) for (auto const &it : c)
#define ALL(c) c.begin(), c.end()
#define TESTS            \
    int tests;           \
    scanf("%d", &tests); \
    REPI(test_index, 1, tests)

#define DEBUGC(c, w)                                                            \
    {                                                                           \
        cout << "[ ";                                                           \
        TR(debug_it, c) { cout << setfill(' ') << setw(w) << debug_it << " "; } \
        cout << "]" << NL;                                                      \
    }
#define DEBUGA(a, n, w)                                                              \
    {                                                                                \
        cout << "[ ";                                                                \
        REP(debug_x, 0, n) { cout << setfill(' ') << setw(w) << a[debug_x] << " "; } \
        cout << "]" << NL;                                                           \
    }
#define DEBUG2A(a, m, n, w)                              \
    {                                                    \
        REP(debug_y, 0, m) { DEBUGA(a[debug_y], n, w); } \
    }
#pragma endregion

typedef pair<int, ii> queue_vertex;
class vertex_compare
{
public:
    bool operator()(const queue_vertex &qv1, const queue_vertex &qv2)
    {
        ii dt1 = qv1.second;
        ii dt2 = qv2.second;
        return dt1.first == dt2.first ? dt1.second > dt2.second : dt1.first < dt2.first; 
    }
};

int main()
{
    TESTS
    {
        int N, M, s, t, p;
        scanf("%d %d %d %d %d", &N, &M, &s, &t, &p);
        vvii G(N+1);
        while (M--)
        {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            G[u].push_back(PAIR(v, c));
            //cout<<"push: "<<u<<" "<<v<<" "<<c<<NL;
        }

        vii dist_toll(N+1, PAIR(INF, -1));
        priority_queue<queue_vertex, vector<queue_vertex>, vertex_compare> pq;
        dist_toll[s] = PAIR(0, -1);
        pq.push(PAIR(s, dist_toll[s]));

        int max_toll = -1;
        while (!pq.empty())
        {
            auto top = pq.top();pq.pop();
            int u = top.first;
            int d = top.second.first;
            int toll = top.second.second;

            //cout<<"pop: "<<u<<" "<<d<<" "<<toll<<" "<<p<<NL;

            if (d < p)
            {
                if (u==t)
                {
                    max_toll = max(max_toll, toll);
                    //cout<<"found_target: "<<max_toll<<" "<<toll<<" "<<NL;
                }
                TR(G[u], vw)
                {
                    int v = vw.first;
                    int w = vw.second;
                    int v_d = d + w;
                    int v_toll = max(w, toll);
                    ii current_v = dist_toll[v];
                    if ((v_d < current_v.first || v_toll > current_v.second) && v_d <= p)
                    {
                        //cout<<"current_v: "<<v<<" "<<current_v.first<<" , "<<current_v.second<<NL;
                        //cout<<"push_v: "<<v<<" "<<v_d<<" "<<" , "<<v_toll<<" "<<NL;
                        pq.push(PAIR(v, PAIR(v_d, v_toll)));
                        dist_toll[v] = PAIR(min(v_d, current_v.first), max(v_toll, current_v.second));
                    }
                }
            }
        }
        printf("%d\n", max_toll);
    }
    return 0;
}