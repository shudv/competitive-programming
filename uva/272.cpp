#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef queue<int> qi;
typedef priority_queue<int> pqi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef unsigned long long int ulli;
typedef long long int ll;

#define get(n) int (n); scanf("%d",&(n))
#define get2(n,m) int (n),(m); scanf("%d %d",&(n),&(m))
#define get3(n,m,k) int (n),(m),(k); scanf("%d %d %d",&(n),&(m),&(k))
#define foreach(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
#define all(c) c.begin(), c.end()

int main()
{
    string is;
    bool quote_opened = false;

    while(getline(cin, is))
    {
        if (is.empty()) break;
        string os;
        for (int i = 0; i<is.length(); i++)
        {
            if (is[i] == '"')
            {
                os.append(quote_opened ? "''" : "``");
                quote_opened = !quote_opened;
            }
            else
            {
                os.push_back(is[i]);
            }
        }
        cout<<os<<endl;
    }
    return 0;
}