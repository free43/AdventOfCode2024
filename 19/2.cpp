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

long long ff(const auto& s, const auto& lu, int idx, auto& dp)
{
    if(s.empty())
        return 1LL;
    if(idx < dp.size() && dp[idx] != -1)
        return dp[idx];
    long long sum = 0;
    for(const auto& ss : lu)
    {
        if(s.starts_with(ss))
        {
            sum += ff(string(next(begin(s), ss.size()), end(s)), lu, idx + ss.size(), dp);
        }
    }
    return dp[idx] = sum;
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
                if(ss.find('\r') != string::npos)
                    ss.pop_back();
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
    long long sum = 0;
    for(const auto& s : ls)
    {
        vector<long long> dp(s.size(), -1);
        sum += ff(s, lu, 0, dp);
    }
    cout << sum << endl;
}