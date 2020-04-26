#include "library/common.h"

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