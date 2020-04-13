#include<bits/stdc++.h>
using namespace std;

typedef long long           ll;
typedef unsigned long long  ull;
typedef vector<int>         vi;
typedef queue<int>          qi;
typedef priority_queue<int> pqi;
typedef vector<vi>          vvi;
typedef pair<int,int>       ii;
typedef set<int>            si;
typedef map<string,int>     msi;

#define REP(i,a,b)  for(int i=int(a); i<int(b); i++)
#define REPI(i,a,b) for(int i=int(a); i<=int(b); i++)
#define TR(c,it)    for (typeof((c).begin()) it=(c).begin(); it!=(c).end(); it++)
#define ALL(c)      c.begin(), c.end()
#define TESTS       int tests; scanf("%d", &tests); REPI(test_index, 1, tests)

#define NL "\n"

int main()
{
    string line;
    while(getline(cin, line))
    {
        if(line.empty())
        {
            cout<<"empty"<<NL;
            cout<<"solve"<<NL;
        }
        else
        {
            cout<<line<<NL;
        }
    }
    cout<<"solve"<<NL;
    return 0;
}