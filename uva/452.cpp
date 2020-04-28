#include "../common.h"

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
        int next = FRONT(Q);

        for (int i = 0; i < G[next].size(); i++)
        {
            int e = G[next][i];
            in_degree[e]--;
            if (in_degree[e] == 0)
            {
                Q.push(e);
            }
        }

        sorted_vertices.PUSH(next);
    }
}

int main()
{
    GET(T);
    cin.ignore();
    cin.ignore();

    while (T--)
    {
        vvi G(26);
        vi W(26), in_degree(26);
        fill(ALL(in_degree), 0);
        fill(ALL(W), 0);

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
                G[from].PUSH(vertexIndex);
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
        for (int i = 0; i < 26; i++)
        {
            if (critical[i] > max)
            {
                max = critical[i];
            }
        }
        cout << max << "\n";
        if (T > 0)
        {
            cout << "\n";
        }
    }
    return 0;
}