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
#include<memory>
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
    unordered_map<string, int> sums;
    int mx = 0;

    for(auto mn : d)
    {
        char dd = mn % 10;
        unordered_set<string> seqs;
        string seq = "";
        
        auto emplace_seq = [&](char dd){
            if(!seqs.contains(seq))
            {
                mx = max(sums[seq] += dd, mx);
                seqs.emplace(seq);
            }
            auto it = find_if(begin(seq), end(seq), [](const auto c){
                return isdigit(c);
            });
            advance(it, 1);
            seq = string(it, end(seq));
        };
        for(int i = 0; i < 2000; ++i)
        {
            mn = calc(mn);
            char nd = mn % 10;
            char diff = nd - dd;
            if(i >= 4)
            { 
                emplace_seq(dd);
            }
            seq += to_string(diff);
            dd = nd;
        }
        emplace_seq(dd);
    }
    
    cout << mx << endl;


    
    
}