#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<optional>
#include<math.h>
#include<unordered_set>
#include<valarray>
#include<stack>
#include<queue>
using namespace std;

bool ff(const auto& s, const auto& lu)
{
    if(s.empty())
        return true;

    for(const auto& ss : lu)
    {
        if(s.starts_with(ss))
        {
            if(ff(string(next(begin(s), ss.size()), end(s)), lu))
                return true;
        }
    }
    return false;
}

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    unordered_set<string> lu;
    vector<string> ls;
    int r = 0;
    while(getline(f, s))
    {
        if(r == 0)
        {
            auto it = begin(s);
            while(it != end(s))
            {
                auto nit = find(it, end(s), ',');
                auto ss = string(it, nit);
                lu.emplace(move(ss));
                if(nit == end(s))
                    break;
                it = next(nit, 2);
            }
        }
        if(r > 1)
        {
            if(s.find('\r') != string::npos)
                s.pop_back();
            ls.emplace_back(move(s));
        }
        r++;
    }
    int sum = 0;
    for(const auto& s : ls)
    {
        sum += ff(s, lu);
    }
    cout << sum << endl;
}