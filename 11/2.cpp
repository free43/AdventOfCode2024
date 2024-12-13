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
#include<deque>
#include<list>
using namespace std;

long long get(auto& dp, long long i, int n)
{
    if(n == 0)
        return 1;
    if(dp[n - 1].count(i) > 0)
        return dp[n - 1][i];
    auto s = to_string(i);
    if(i == 0)
    {
        return dp[n - 1][i] = get(dp, 1, n - 1);
    }
    if((s.size() & 1) == 0)
    {
        string fh(begin(s), next(begin(s), s.size() / 2));
        string sh(next(begin(s), s.size() / 2), end(s));
        return dp[n - 1][i] = get(dp, stoll(fh), n - 1) + get(dp, stoll(sh), n - 1);
    }
    return dp[n - 1][i] = get(dp, i * 2024, n - 1);
}


int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    deque<long long> ll;
    while(getline(f, s))
    {
        long long l;
        stringstream ss(move(s));
        while(ss >> l)
        {
            ll.emplace_back(l);
        }
    }
    vector<unordered_map<long long, long long>> dp(75);
    long long sum = 0;
    for(auto i : ll)
    {
        sum += get(dp, i, 75);
    }
    cout << sum << endl;

}