#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef queue<int> qi;
typedef priority_queue<int> pqi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef unsigned long long int ulli;
typedef long long int ll;

#define get(n) \
    int(n);    \
    scanf("%d", &(n))
#define get2(n, m) \
    int(n), (m);   \
    scanf("%d %d", &(n), &(m))
#define get3(n, m, k) \
    int(n), (m), (k); \
    scanf("%d %d %d", &(n), &(m), &(k))
#define foreach(i, t) for (typeof(t.begin()) i = t.begin(); i != t.end(); i++)
#define all(c) c.begin(), c.end()
#define TESTS get(tests); while (tests--)

void topological_sort(const vvi &G, vi &in_degree, vi &sorted_vertices)
{
    qi Q;

    for (int i = 0; i < in_degree.size(); i++)
    {
        if (in_degree[i] == 0)
        {
            Q.push(i);
        }
    }

    while (!Q.empty())
    {
        int next = Q.front();
        Q.pop();

        for (int i = 0; i < G[next].size(); i++)
        {
            int e = G[next][i];
            in_degree[e]--;
            if (in_degree[e] == 0)
            {
                Q.push(e);
            }
        }

        sorted_vertices.push_back(next);
    }
}

int main()
{
    get(T);
    cin.ignore();
    cin.ignore();

    while (T--)
    {
        vvi G(26);
        vi W(26), in_degree(26);
        fill(all(in_degree), 0);
        fill(all(W), 0);

        string line;
        while (getline(cin, line) && line != "")
        {
            char vertex;
            int weight;
            string edges;
            stringstream ss(line);
            ss >> vertex >> weight >> edges;

            int vertexIndex = vertex - 'A';
            W[vertexIndex] = weight;
            in_degree[vertexIndex] = edges.size();
            for (int i = 0; i < edges.size(); i++)
            {
                int from = edges[i] - 'A';
                G[from].push_back(vertexIndex);
            }
        }

        vi sorted_vertices;
        topological_sort(G, in_degree, sorted_vertices);

        vi critical(26);

        for (int i = 0; i < 26; i++)
        {
            critical[i] = W[i];
        }

        for (int i = 0; i < sorted_vertices.size(); i++)
        {
            int next = sorted_vertices[i];
            int w = W[next];
            for (int j = 0; j < G[next].size(); j++)
            {
                int v = G[next][j];
                if (critical[next] + W[v] > critical[v])
                {
                    critical[v] = critical[next] + W[v];
                }
            }
        }

        int max = -1;
        for (int i=0; i<26; i++)
        {
            if (critical[i] > max)
            {
                max = critical[i];
            }
        }
        cout<<max<<"\n";
        if (T>0)
        {
            cout<<"\n";
        }
    }
    return 0;
}