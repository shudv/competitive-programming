#include "../common.h"

#define MAX_H 205
#define MAX_W 205
int I[MAX_H][MAX_W];
int H, W;
char glyph[] = {'W', 'A', 'K', 'J', 'S', 'D'};

int V[1000];

void print()
{
    cout << "********************************" << NL;
    REP(i, H)
    {
        REP(j, W)
        {
            printf("%d ", I[i][j]);
        }
        printf("\n");
    }
}

void init()
{
    V['0'] = 0;
    V['1'] = 1;
    V['2'] = 2;
    V['3'] = 3;
    V['4'] = 4;
    V['5'] = 5;
    V['6'] = 6;
    V['7'] = 7;
    V['8'] = 8;
    V['9'] = 9;
    V['a'] = 10;
    V['b'] = 11;
    V['c'] = 12;
    V['d'] = 13;
    V['e'] = 14;
    V['f'] = 15;
}

void mark_index(int a, int b, int index)
{
    qii Q;
    I[a][b] = index;
    Q.push(PAIR(a, b));

    while (!Q.empty())
    {
        ii next = FRONT(Q);
        REPI(i, next.first - 1, next.first + 1)
        REPI(j, next.second - 1, next.second + 1)
        {
            if (i >= 0 && i < H && j >= 0 && j < W && !(i == next.first && j == next.second) && I[i][j] == 0)
            {
                I[i][j] = index;
                Q.push(PAIR(i, j));
            }
        }
    }
}

void mark()
{
    int next_index = 1;
    REP(i, H)
    REP(j, W)
    {
        if (I[i][j] == 0)
        {
            next_index++;
            mark_index(i, j, next_index);
        }
    }
}

int traverse_glyph(int a, int b)
{
    si holes;
    qii Q;
    I[a][b] = 0;
    Q.push(PAIR(a, b));

    while (!Q.empty())
    {
        ii next = FRONT(Q);
        REPI(i, next.first - 1, next.first + 1)
        REPI(j, next.second - 1, next.second + 1)
        {
            if (i >= 0 && i < H && j >= 0 && j < W && !(i == next.first && j == next.second))
            {
                if (I[i][j] > 1)
                {
                    holes.insert(I[i][j]);
                }
                else if (I[i][j] == 1)
                {
                    I[i][j] = 0;
                    Q.push(PAIR(i, j));
                }
            }
        }
    }

    return holes.size() - 1;
}

string find_glyphs()
{
    string glyphs;
    REP(i, H)
    REP(j, W)
    {
        if (I[i][j] == 1)
        {
            si holes;
            glyphs.PUSH(glyph[traverse_glyph(i, j)]);
        }
    }
    sort(ALL(glyphs));
    return glyphs;
}

int main()
{
    init();
    int caseNo = 1;
    do
    {
        memset(I, 0, sizeof I);
        scanf("%d %d", &H, &W);
        if (H == 0 || W == 0)
            break;

        REP(i, H)
        {
            string line;
            cin >> line;
            REP(j, W)
            {
                int value = V[line[j]];
                REP(k, 4)
                {
                    I[i + 1][(4 * j) + k + 1] = (value & (1 << (4 - (k + 1)))) > 0 ? 1 : 0;
                }
            }
        }
        W *= 4;
        H += 2;
        W += 2;
        //print();
        mark();
        //print();
        cout << "Case " << caseNo++ << ": " << find_glyphs() << NL;
    } while (true);
    return 0;
}
