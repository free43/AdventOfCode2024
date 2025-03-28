#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<optional>
#include<math.h>
#include<unordered_set>
#include<valarray>
#include<span>
using namespace std;

auto comb(auto v0, auto v1)
{
    const auto tmp= v1;
    while(v1 > 0)
    {
        v0 *= 10;
        v1 /= 10;
    }
    return v0 + tmp;
}

bool check(const auto goal, const auto& d, const int i, const auto acc)
{
    if(i >= d.size())
        return acc == goal;
    bool b = check(goal, d, i + 1, d[i] * acc);
    if(b)
        return true;
    b = check(goal, d, i + 1, d[i] + acc);
    if(b)
        return true;
    b = check(goal, d, i + 1, comb(acc, d[i]));
    return b;
    
}

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    vector<vector<long long>> d;
    string s;
    while(getline(f, s))
    {
        istringstream ss(move(s));
        unsigned long long i;
        char c;
        ss >> i >> c;
        d.emplace_back();
        d.back().emplace_back(i);
        while(ss >> i)
        {
            d.back().emplace_back(i);
        }
    }
    long long sum = 0;
    for(const auto& v : d)
    {
        long long goal = v[0];
        vector<long long> vv(next(begin(v), 2), end(v));
        sum += goal * check(goal, vv, 0, v[1]);
    }
    cout << sum << endl;
}