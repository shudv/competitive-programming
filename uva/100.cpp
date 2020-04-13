#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef queue<int> qi;
typedef priority_queue<int> pqi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef unsigned long long int ulli;
typedef long long int lli;

#define get(n) int (n); scanf("%d",&(n))
#define get2(n,m) int (n),(m); scanf("%d %d",&(n),&(m))
#define get3(n,m,k) int (n),(m),(k); scanf("%d %d %d",&(n),&(m),&(k))
#define foreach(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
#define all(c) c.begin(), c.end()

int cycle_length(lli n)
{
    int length = 1;
    while (n!=1)
    {
        if (n%2 == 0)
        {
            length += 1;
            n /= 2;
        }
        else
        {
            length += 2;
            n = (3 * (n/2)) + 2;
        }
    }
    return length;
}

int main()
{
    int a,b;
    while(cin>>a>>b)
    {
        int max_length = 0;
        for (int i=min(a, b); i<=max(a, b); i++)
        {
            int length = cycle_length((lli)i);
            if (length > max_length) max_length = length;    
        }
        cout<<a<<" "<<b<<" "<<max_length<<endl;
    }
    return 0;
}
