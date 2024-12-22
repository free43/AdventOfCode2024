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
#include<map>
using namespace std;

auto prune(const auto& i)
{   
    return i % 16777216LL;
}
auto mix(const auto& i, const auto& sn)
{   
    return i ^ sn;
}

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    vector<long long> d;
    while(getline(f, s))
    {
        d.emplace_back(stoll(s));
    }

    auto calc = [](const auto& sn){
        auto ns = prune(mix(sn * 64LL, sn));
        ns = prune(mix(ns / 32LL, ns));
        ns = prune(mix(ns * 2048LL, ns));
        return ns;
    };
    long long sum = 0;
    for(auto mn : d)
    {
        for(int i = 0; i < 2000; ++i)
        {
            mn = calc(mn);
        }
        sum += mn;
    }
    cout << sum << endl;


    
    
}