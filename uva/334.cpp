#include "../common.h"

#define MAXN 200

int main()
{
    int case_number = 1;
    while (true)
    {
        GET(n);
        if (n == 0)
            break;

        msi name_index;
        vector<string> names;

        vvi W(MAXN, vi(MAXN, MAXN));

        REP(n)
        {
            GET(c);

            vi computation;
            REP(c)
            {
                string name;
                cin >> name;

                if (!HAS(name_index, name))
                {
                    int index = names.size();
                    name_index[name] = index;
                    names.PUSH(name);
                }

                int index = name_index[name];
                computation.PUSH(index);
            }

            REP(i, computation.size() - 1)
            W[computation[i]][computation[i + 1]] = 1;
        }

        GET(m);
        REP(m)
        {
            string name1, name2;
            cin >> name1 >> name2;
            W[name_index[name1]][name_index[name2]] = 1;
        }

        int N = names.size();

        REP(k, N)
        REP(u, N)
        REP(v, N)
        W[u][v] = MIN(W[u][v], W[u][k] + W[k][v]);

        vii concurrent_events;
        REP(u, N)
        REP(v, u+1, N)
        if (W[u][v] == MAXN && W[v][u] == MAXN)
            concurrent_events.PUSH(PAIR(u, v));

        if (concurrent_events.size() > 0)
        {
            printf("Case %d, %d concurrent events:\n", case_number, concurrent_events.size());
            int count = MIN((int)concurrent_events.size(), 2);
            REP(count)
                cout << "(" << names[concurrent_events[i].first] << "," << names[concurrent_events[i].second] << ") ";
        }
        else
            printf("Case %d, no concurrent events.", case_number);
        printf(NL);
        case_number++;
    }
    return 0;
}