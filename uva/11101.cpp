#include "../common.h"

#define MAXN 2005
int dist[MAXN][MAXN];
vii neighbours = {PAIR(0, -1), PAIR(-1, 0), PAIR(+1, 0), PAIR(0, +1)};

int bfs(vii &mall)
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
        int neighbour_least_distance = distance + 1;
        TR(neighbour, neighbours)
        {
            int neighbour_x = next.first + neighbour.first;
            int neighbour_y = next.second + neighbour.second;

            if (neighbour_x >= 0 && neighbour_x < MAXN && neighbour_y >= 0 && neighbour_y < MAXN)
            {
                int neighbour_distance = dist[neighbour_x][neighbour_y];

                // If other mall is found return distance
                if (neighbour_distance == -1)
                    return neighbour_least_distance;

                // Else update distance if it is smaller
                if (neighbour_least_distance < neighbour_distance)
                {
                    dist[neighbour_x][neighbour_y] = neighbour_least_distance;
                    Q.push(PAIR(neighbour_x, neighbour_y));
                    //cout<<"push "<<neighbour_x<<","<<neighbour_y<<":"<<neighbour_least_distance<<NL;
                    //print();
                }
            }
        }
    } while (!Q.empty());
    return -1;
}

int main()
{
    do
    {
        REP(i, 0, MAXN)
        REP(j, 0, MAXN) dist[i][j] = 9999;

        //print();
        // source mall
        vii source_mall;
        int n;
        cin >> n;
        if (n == 0)
            return 0;

        while (n--)
        {
            int x, y;
            cin >> x >> y;
            source_mall.push_back(PAIR(x, y));
            // Mall's vertices are at 0 distance from itself
            dist[x][y] = 0;
        }

        // target mall
        cin >> n;
        while (n--)
        {
            int x, y;
            cin >> x >> y;
            // mark target veriices distinctly
            dist[x][y] = -1;
        }

        // DEBUG2A(dist, 5, 5, 5);
        printf("%d\n", bfs(source_mall));
        //print();
    } while (true);
    return 0;
}