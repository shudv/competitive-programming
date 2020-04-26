#include "../common.h"

int cycle_length(ll n)
{
    int length = 1;
    while (n != 1)
    {
        if (n % 2 == 0)
        {
            length += 1;
            n /= 2;
        }
        else
        {
            length += 2;
            n = (3 * (n / 2)) + 2;
        }
    }
    return length;
}

int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        int max_length = 0;
        for (int i = min(a, b); i <= max(a, b); i++)
        {
            int length = cycle_length((ll)i);
            if (length > max_length)
                max_length = length;
        }
        cout << a << " " << b << " " << max_length << endl;
    }
    return 0;
}
